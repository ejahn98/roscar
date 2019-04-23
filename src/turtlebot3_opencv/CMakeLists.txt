cmake_minimum_required(VERSION 2.8.3)
project(turtlebot3_opencv)


find_package(catkin REQUIRED COMPONENTS 
  cv_bridge
  roscpp
  std_msgs
  
  geometry_msgs
  sensor_msgs
)

catkin_package(
  LIBRARIES turtlebot3_lidar
  CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs
)


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

catkin_package( 
  LIBRARIES turtlebot3_opencv
    CATKIN_DEPENDS cv_bridge roscpp std_msgs
)

include_directories(   
  ${catkin_INCLUDE_DIRS} 
) 

add_executable(${PROJECT_NAME}_node src/turtlebot3_opencv_node.cpp) 
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS}
${catkin_EXPORTED_TARGETS}) 
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES} 
  ${OpenCV_LIBS}
)


























