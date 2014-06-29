#include <ros/ros.h>
#include <task_buoy/buoy_server.h>
#define PI 3.1414

Buoy::Buoy(std::string name) : _it(_n), _s(_n, name, boost::bind(&Buoy::executeCB, this, _1), false), _actionName(name)
{
    _sub = _it.subscribe("/kraken/front_camera", 1, &Buoy::imageCallBack, this);
    _pub = _it.advertise("/kraken/processed/buoy_image", 1);

    ifstream _thresholdVal("threshold.th");
    if(_thresholdVal.is_open())
    {
        for(int i = 0; i < 3; i++)
        {
            _thresholdVal >> _lowerThreshRed1[i];
        }
        for(int i = 0; i < 3; i++)
        {
            _thresholdVal >> _upperThreshRed1[i];
        }
        for(int i = 0; i < 3; i++)
        {
            _thresholdVal >> _lowerThreshRed2[i];
        }
        for(int i = 0; i < 3; i++)
        {
            _thresholdVal >> _upperThreshRed2[i];
        }
        for(int i = 0; i < 3; i++)
        {
            _thresholdVal >> _lowerThreshGreen[i];
        }
        for(int i = 0; i < 3; i++)
        {
            _thresholdVal >> _upperThreshGreen[i];
        }
    }
    else
    {
        ROS_ERROR("Unable to open threshold file.");
        ros::shutdown();
    }
    _kernelDilateErode = getStructuringElement(MORPH_RECT, Size(3,3));
    _finalImage.encoding = "mono8";
    _s.start();
}

void Buoy::imageCallBack(const sensor_msgs::ImageConstPtr &_msg)
{
    cv_bridge::CvImagePtr _imagePtr;
    try
    {
        _imagePtr = cv_bridge::toCvCopy(_msg, "bgr8");
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", _msg->encoding.c_str());
    }
    _image = _imagePtr->image;
}

void Buoy::executeCB(const actionmsg::buoyGoalConstPtr &_goal)
{
    ros::Rate looprate(10);
    bool success = true;

    switch(_goal->order)
    {
        case DETECT_BUOY:
        {
            bool _detected = false;
            while(ros::ok())
            {
                if (_s.isPreemptRequested() || !ros::ok())
                {
                    ROS_INFO("%s: Preempted", _actionName.c_str());
                    _s.setPreempted();
                    success = false;
                    break;
                }
                _detected = detectBuoy();
                _finalImage.image = _imageBW;
                _finalImagemsg = _finalImage.toImageMsg();
                _pub.publish(_finalImagemsg);

                if(_detected)
                {
                    _result.sequence.push_back(BUOY_DETECTED);
                    break;
                }
                looprate.sleep();
            }
            break;
        }
        case ALIGN_BUOY:
        {
            while(ros::ok())
            {
                if (_s.isPreemptRequested() || !ros::ok())
                {
                    ROS_INFO("%s: Preempted", _actionName.c_str());
                    _s.setPreempted();
                    success = false;
                    break;
                }
                detectBuoy();
                getAllignment();
                _finalImage.image = _imageBW;
                _finalImagemsg = _finalImage.toImageMsg();
                _pub.publish(_finalImagemsg);
                if((_feedback.errorx < 5 && _feedback.errorx > -5) && (_feedback.errory > -5 && _feedback.errory < 5))
                {
                    _result.sequence.push_back(BUOY_ALIGNED);
                    break;
                }
                _s.publishFeedback(_feedback);
                looprate.sleep();
            }
            break;
        }
    }

    if(success)
    {
        _result.sequence.push_back(_goal->order);
        _s.setSucceeded(_result);
    }
}

bool Buoy::detectBuoy()
{
    if(!_image.empty())
    {
        cvtColor(_image, _imageHSV, CV_BGR2HSV);

        inRange(_imageHSV,_lowerThreshRed1,_upperThreshRed1, _imageBW);
        inRange(_imageHSV,_lowerThreshRed2,_upperThreshRed2, _imageBWRed);
        add(_imageBW, _imageBWRed, _imageBW);
        
        inRange(_imageHSV,_lowerThreshGreen,_upperThreshGreen, _imageBWGreen);
        add(_imageBW, _imageBWGreen, _imageBW);
        medianBlur(_imageBW, _imageBW, 3);
        erode(_imageBW, _imageBW, _kernelDilateErode);
        CBlobResult _blobs,_blobsClutter;
        CBlob * _currentBlob;
        IplImage _imageBWipl = _imageBW;

        _blobs = CBlobResult(&_imageBWipl, NULL, 0);
        _blobs.Filter(_blobs, B_INCLUDE, CBlobGetArea(), B_INSIDE, 1, 1000);

        _blobsClutter = CBlobResult(&_imageBWipl, NULL, 255);
        _blobsClutter.Filter(_blobsClutter, B_INCLUDE, CBlobGetArea(), B_INSIDE, 25, 1000);

        for(int i = 0; i < _blobs.GetNumBlobs(); i++)
        {
            _currentBlob = _blobs.GetBlob(i);
            _currentBlob->FillBlob(&_imageBWipl, Scalar(255));
        }
        
        for(int i = 0; i < _blobsClutter.GetNumBlobs(); i++)
        {
            _currentBlob = _blobsClutter.GetBlob(i);
            _currentBlob->FillBlob(&_imageBWipl, Scalar(0));
        }

        Mat _imageBW2 = _imageBW.clone();

        _contours.clear();
        medianBlur(_imageBW2, _imageBW2, 5);
        findContours(_imageBW2, _contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

        Point2f _centerBuff;
        float _radiusBuff;
        vector<Point> _contoursPolyBuff;
        _center.clear();
        _radius.clear();
        _contoursPoly.clear();

        for(int i=0; i < _contours.size(); i++)
        {
            if(contourArea(_contours[i])>50)
            {
               approxPolyDP(_contours[i],_contoursPolyBuff,3,true);
               minEnclosingCircle((Mat)_contoursPolyBuff,_centerBuff,_radiusBuff);
               circle(_imageBW,_centerBuff,_radiusBuff,Scalar(0,255,0));
               _center.push_back(_centerBuff);
               _radius.push_back(_radiusBuff);
               _contoursPoly.push_back(_contoursPolyBuff);
            }
        }

        if(_center.size() > 0)
            return true;
        else
            return false;
    }
    else
        return false;
}

void Buoy::getAllignment()
{
    for(int i = 0; i < _center.size(); i++)
    {
        _feedback.errorx = _image.cols/2 - _center[i].x;
        _feedback.errory = _image.rows/2 - _center[i].y;
        cout<< _feedback.errorx << " : " << _feedback.errory << endl;
    }
}

Buoy::~Buoy()
{

}

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "buoy_server");
    Buoy _buoyserver("buoy");
    ros::spin();
    return 0;
}
