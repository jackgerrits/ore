cmake_minimum_required(VERSION 3.6.2)
project(ore)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm CONFIG REQUIRED)

# TODO move catch, stb_image and tiny_obj_loader to external dependencies

set(ore_headers
  include/ore/components/camera_component.hpp
  include/ore/components/component.hpp
  include/ore/components/light_component.hpp
  include/ore/components/model_component.hpp
  include/ore/components/position_3d_component.hpp
  include/ore/entity_manager.hpp
  include/ore/entity.hpp
  include/ore/image.hpp
  include/ore/loader.hpp
  include/ore/material.hpp
  include/ore/model.hpp
  include/ore/shaders/entity_shader.hpp
  include/ore/shaders/shader_program.hpp
  include/ore/systems/camera_system.hpp
  include/ore/systems/entity_render_system.hpp
  include/ore/systems/system.hpp
)

set(ore_sources
  src/components/component.cpp
  src/entity.cpp
  src/image.cpp
  src/lib/stb_image.cpp
  src/lib/tiny_obj_loader.cpp
  src/loader.cpp
  src/material.cpp
  src/model.cpp
  src/shaders/entity_shader.cpp
  src/shaders/shader_program.cpp
  src/systems/camera_system.cpp
)

add_library(ore ${ore_sources} ${ore_headers})

configure_file(include/ore/base_dir.h.in base_dir.h)
target_link_libraries(ore PUBLIC OpenGL::GL GLUT::GLUT GLEW::GLEW glm)
target_include_directories(ore PUBLIC include ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ore_test
  test/component_tests.cpp test/entity_manager_tests.cpp test/entity_tests.cpp
  test/loader_tests.cpp test/main.cpp)
target_link_libraries(ore_test ore)

add_subdirectory(examples)