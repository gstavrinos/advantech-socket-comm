cmake_minimum_required(VERSION 3.0.2)
project(advantech_socket_comm)

set(CMAKE_CXX_FLAGS "-std=c++14")

# set(BIODAQDIR $ENV{BIODAQDIR})
set(BIODAQDIR /opt/advantech)
find_library(BIODAQLIB biodaq ${BIODAQDIR}/libs REQUIRED)

include_directories(include ${BIODAQDIR}/inc)

set(LIBRARY_TARGET_NAME advantech_comm)

set(${LIBRARY_TARGET_NAME}_SRC
    src/.advantech_comm.cpp
)

set(${LIBRARY_TARGET_NAME}_HDR
    include/advantech_comm/advantech_comm.hpp
)

add_library(${LIBRARY_TARGET_NAME} SHARED
    src/advantech_comm.cpp
)

install(TARGETS ${LIBRARY_TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

target_link_libraries(${LIBRARY_TARGET_NAME} ${BIODAQLIB})

add_executable(${PROJECT_NAME} src/comm.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBRARY_TARGET_NAME})

