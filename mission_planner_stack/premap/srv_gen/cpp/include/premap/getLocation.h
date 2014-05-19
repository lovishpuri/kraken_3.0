/* Auto-generated by genmsg_cpp for file /home/prudhvi/ros_ws/premap/srv/getLocation.srv */
#ifndef PREMAP_SERVICE_GETLOCATION_H
#define PREMAP_SERVICE_GETLOCATION_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "ros/service_traits.h"




namespace premap
{
template <class ContainerAllocator>
struct getLocationRequest_ {
  typedef getLocationRequest_<ContainerAllocator> Type;

  getLocationRequest_()
  : id(0)
  {
  }

  getLocationRequest_(const ContainerAllocator& _alloc)
  : id(0)
  {
  }

  typedef int32_t _id_type;
  int32_t id;


  typedef boost::shared_ptr< ::premap::getLocationRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::premap::getLocationRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct getLocationRequest
typedef  ::premap::getLocationRequest_<std::allocator<void> > getLocationRequest;

typedef boost::shared_ptr< ::premap::getLocationRequest> getLocationRequestPtr;
typedef boost::shared_ptr< ::premap::getLocationRequest const> getLocationRequestConstPtr;



template <class ContainerAllocator>
struct getLocationResponse_ {
  typedef getLocationResponse_<ContainerAllocator> Type;

  getLocationResponse_()
  : x(0.0)
  , y(0.0)
  {
  }

  getLocationResponse_(const ContainerAllocator& _alloc)
  : x(0.0)
  , y(0.0)
  {
  }

  typedef float _x_type;
  float x;

  typedef float _y_type;
  float y;


  typedef boost::shared_ptr< ::premap::getLocationResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::premap::getLocationResponse_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct getLocationResponse
typedef  ::premap::getLocationResponse_<std::allocator<void> > getLocationResponse;

typedef boost::shared_ptr< ::premap::getLocationResponse> getLocationResponsePtr;
typedef boost::shared_ptr< ::premap::getLocationResponse const> getLocationResponseConstPtr;


struct getLocation
{

typedef getLocationRequest Request;
typedef getLocationResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct getLocation
} // namespace premap

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::premap::getLocationRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::premap::getLocationRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::premap::getLocationRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "c5e4a7d59c68f74eabcec876a00216aa";
  }

  static const char* value(const  ::premap::getLocationRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xc5e4a7d59c68f74eULL;
  static const uint64_t static_value2 = 0xabcec876a00216aaULL;
};

template<class ContainerAllocator>
struct DataType< ::premap::getLocationRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "premap/getLocationRequest";
  }

  static const char* value(const  ::premap::getLocationRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::premap::getLocationRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int32 id\n\
\n\
";
  }

  static const char* value(const  ::premap::getLocationRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::premap::getLocationRequest_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::premap::getLocationResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::premap::getLocationResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::premap::getLocationResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "ff8d7d66dd3e4b731ef14a45d38888b6";
  }

  static const char* value(const  ::premap::getLocationResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xff8d7d66dd3e4b73ULL;
  static const uint64_t static_value2 = 0x1ef14a45d38888b6ULL;
};

template<class ContainerAllocator>
struct DataType< ::premap::getLocationResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "premap/getLocationResponse";
  }

  static const char* value(const  ::premap::getLocationResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::premap::getLocationResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float32 x\n\
float32 y\n\
\n\
";
  }

  static const char* value(const  ::premap::getLocationResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::premap::getLocationResponse_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::premap::getLocationRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.id);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct getLocationRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::premap::getLocationResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.x);
    stream.next(m.y);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct getLocationResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<premap::getLocation> {
  static const char* value() 
  {
    return "1de201f083ea35a06514be7769efdb42";
  }

  static const char* value(const premap::getLocation&) { return value(); } 
};

template<>
struct DataType<premap::getLocation> {
  static const char* value() 
  {
    return "premap/getLocation";
  }

  static const char* value(const premap::getLocation&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<premap::getLocationRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "1de201f083ea35a06514be7769efdb42";
  }

  static const char* value(const premap::getLocationRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<premap::getLocationRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "premap/getLocation";
  }

  static const char* value(const premap::getLocationRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<premap::getLocationResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "1de201f083ea35a06514be7769efdb42";
  }

  static const char* value(const premap::getLocationResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<premap::getLocationResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "premap/getLocation";
  }

  static const char* value(const premap::getLocationResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // PREMAP_SERVICE_GETLOCATION_H
