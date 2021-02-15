cmake_minimum_required(VERSION 3.0.2)
project(advantech_ros_comm)

add_compile_options(-std=c++14)

find_library(advantech_comm REQUIRED)

find_package(catkin REQUIRED
    roscpp
    roboskel_msgs
)

catkin_package(
    CATKIN_DEPENDS roscpp roboskel_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/advantech_ros_comm.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} advantech_comm)

