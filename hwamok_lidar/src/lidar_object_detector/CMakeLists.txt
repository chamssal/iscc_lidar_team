cmake_minimum_required(VERSION 3.0.2)
project(lidar_object_detector)

find_package(catkin REQUIRED COMPONENTS
  pcl_conversions
  pcl_ros
  roscpp
  sensor_msgs
  visualization_msgs
  nav_msgs
  geometry_msgs
  std_msgs
  message_generation
  dynamic_reconfigure
)

find_package(PCL 1.8 REQUIRED)

add_message_files(
    FILES
    Waypoint.msg
    Boundingbox.msg
    DriveValues.msg
    Delivery.msg
    DynamicVelocity.msg
    TrafficCone.msg
    )
    
generate_messages(
    DEPENDENCIES
    sensor_msgs
    std_msgs
    geometry_msgs
    nav_msgs
    )

generate_dynamic_reconfigure_options(
    cfg/traffic_hyper_parameter.cfg
    )

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES lidar_object_detector
    CATKIN_DEPENDS pcl_conversions pcl_ros roscpp sensor_msgs visualization_msgs nav_msgs geometry_msgs std_msgs dynamic_reconfigure
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${PCL_INCLUDE_DIRS}
    ${CATKIN_DEVEL_PREFIX}/include
    )
    
add_executable(traffic_cone src/traffic_cone.cpp)
target_link_libraries(traffic_cone ${catkin_LIBRARIES} ${PCL_LIBRARIES})
add_dependencies(traffic_cone ${PROJECT_NAME}_gencfg)