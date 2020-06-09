cmake_minimum_required(VERSION 2.8.3)
project(lidar_homework)
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

 find_package(catkin REQUIRED COMPONENTS
    pcl_conversions
    pcl_ros
    roscpp
    sensor_msgs
 )


catkin_package(
#  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  #include
)
add_executable(lidar_homework_node src/lidar_homework.cpp)
#add_dependencies(imu_tutorial_node imu_tutorial_generate_messages_cpp)

target_link_libraries(lidar_homework_node
  ${catkin_LIBRARIES}
)

#install(TARGETS lidar_tutorial_node
#  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)
