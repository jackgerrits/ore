cmake_minimum_required(VERSION 3.6.2)
project(ore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(external EXCLUDE_FROM_ALL)

# TODO move catch to external dependencies

set(ore_headers
        include/ore/components/camera_component.h
        include/ore/components/component.h
        include/ore/components/light_component.h
        include/ore/components/model_component.h
        include/ore/components/position_3d_component.h
        include/ore/entity_manager.h
        include/ore/entity.h
        include/ore/image.h
        include/ore/loader.h
        include/ore/material.h
        include/ore/model.h
        include/ore/shaders/entity_shader.h
        include/ore/shaders/shader_program.h
        include/ore/systems/camera_system.h
        include/ore/systems/entity_render_system.h
        include/ore/systems/system.h
        include/ore/window.h include/ore/util/vec_print.h)

set(ore_sources
        src/components/component.cpp
        src/entity.cpp
        src/image.cpp
        src/loader.cpp
        src/material.cpp
        src/model.cpp
        src/shaders/entity_shader.cpp
        src/shaders/shader_program.cpp
        src/systems/camera_system.cpp
        src/window.cpp)

add_library(ore ${ore_sources} ${ore_headers})

configure_file(include/ore/base_dir.h.in base_dir.h)
target_link_libraries(ore PUBLIC glad::glad OpenGL::GL glfw fmt::fmt stb_image tiny_obj_loader ${CMAKE_DL_LIBS})
# Vcpkg exports the target, but the default find_package does not. This is a
# quick hack since the dependencies on Windows are usually with vcpkg and usually
# apt (or some other system package manager) on Ubuntu
if (MSVC)
    target_link_libraries(ore PRIVATE glm)
else ()
    target_include_directories(ore PRIVATE ${GLM_INCLUDE_DIRS})
endif ()
target_include_directories(ore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ore_test
        test/component_tests.cpp test/entity_manager_tests.cpp test/entity_tests.cpp
        test/loader_tests.cpp test/main.cpp)
target_link_libraries(ore_test ore)

add_subdirectory(examples)
