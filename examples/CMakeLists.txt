find_package(glfw3 CONFIG REQUIRED)

add_executable(basic_example basic.cpp)
target_link_libraries(basic_example PRIVATE glfw ore)