cmake_minimum_required(VERSION 2.8.3)
project(grull_transform_pointcloud)
find_package(catkin REQUIRED COMPONENTS sensor_msgs pcl_ros tf)
find_package(PCL REQUIRED)
catkin_package()
include_directories(${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})
add_library(transform_pointcloud src/transform_pointcloud.cpp)
target_link_libraries(transform_pointcloud ${catkin_LIBRARIES} ${PCL_LIBRARIES})
install(TARGETS transform_pointcloud
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

