cmake_minimum_required(VERSION 2.8.3)
project(turtlebot3_lidar)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs 
)

catkin_package(
  LIBRARIES turtlebot3_lidar
  CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/turtlebot3_lidar_node.cpp)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS}
${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node
 ${catkin_LIBRARIES}
)
  