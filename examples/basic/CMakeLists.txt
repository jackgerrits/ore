find_package(glfw3 CONFIG REQUIRED)

add_executable(basic_example
  basic.cpp basic_shader.cpp resource_path.hpp.in basic.frag basic.vert basic_render_system.h basic_shader.h)
target_link_libraries(basic_example PRIVATE ore glfw)

configure_file(resource_path.hpp.in resource_path.hpp)
target_include_directories(basic_example PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
