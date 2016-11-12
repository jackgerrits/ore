cmake_minimum_required(VERSION 3.6.2)
project(ore)
set(CMAKE_BUILD_TYPE Release)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# To install the library
# install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib)
