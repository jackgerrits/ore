cmake_minimum_required(VERSION 3.6.2)
project(ore)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL dependencies on system.
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR " OpenGL not found!")
endif(NOT OPENGL_FOUND)

find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
    message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)

find_package(GLUT)
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found. Ignore if values defined as arguments.")
endif(NOT GLUT_FOUND)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${GLM_INCLUDE_DIR})

# Include source of project.
include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Compile project as a shared library.
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Link dependencies.
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLUT_LIBRARIES})
