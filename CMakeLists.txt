cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ore)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find OpenGL dependencies on system.
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR " OpenGL not found!")
endif(NOT OPENGL_FOUND)

find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
    message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

# Include source of project.
include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Compile project as a shared library.
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Link dependencies.
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
