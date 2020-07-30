find_package(glfw3 CONFIG REQUIRED)

configure_file(resource_path.h.in resource_path.h)
add_executable(barrel_example barrel.cpp)
target_include_directories(barrel_example PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(barrel_example PRIVATE ore glfw)
