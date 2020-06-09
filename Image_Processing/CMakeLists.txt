cmake_minimum_required(VERSION 2.8.3)
project(hw4_image)
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  image_transport
)

find_package( OpenCV REQUIRED )
find_package( cv_bridge REQUIRED )

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs image_transport
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${cv_bridge_INCLUDE_DIRS}
)

add_executable(img_node src/img_node.cpp)

target_link_libraries(img_node
  ${OpenCV_LIBS}
  ${catkin_LIBRARIES}
  ${cv_bridge_LIBRARIES}
)
