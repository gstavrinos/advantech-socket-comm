cmake_minimum_required(VERSION 3.0.2)
project(advantech_socket_comm)

set(CMAKE_CXX_FLAGS "-std=c++14")

# set(BIODAQDIR $ENV{BIODAQDIR})
set(BIODAQDIR /opt/advantech)
find_library(BIODAQLIB biodaq ${BIODAQDIR}/libs REQUIRED)

include_directories(${BIODAQDIR}/inc)

add_executable(${PROJECT_NAME} src/comm.cpp)
target_link_libraries(${PROJECT_NAME} ${BIODAQLIB})

