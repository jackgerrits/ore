#include <ore/window.h>

#include <iostream>
void error_callback(int /*error*/, const char* description) {
    fputs(description, stderr);
}

ore::window::window() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::exit(1);
    }

    // Specify that we want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window and OpenGL context
    win_x = 1024;
    win_y = 768;
    m_window =
        glfwCreateWindow(win_x, win_y, "OpenGL Car Game", nullptr, nullptr);
    if (m_window == nullptr) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwSetWindowUserPointer(m_window, this);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    if (!gladLoadGL()) {
        std::cerr << "Failed to load OpenGL" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwGetFramebufferSize(m_window, &win_x, &win_y);

    // Sets the (background) colour for each time the frame-buffer
    // (colour buffer) is cleared
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    //    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ore::window::key_callback(GLFWwindow* win, int key, int scancode,
                               int action, int mods) {
    auto* this_window = (window*)glfwGetWindowUserPointer(win);
    this_window->m_key_callback(win, key, scancode, action, mods);
}

void ore::window::mouse_pos_callback(GLFWwindow* win, double x, double y) {
    auto* this_window = (window*)glfwGetWindowUserPointer(win);
    this_window->m_mouse_pos_callback(win, x, y);
}

void ore::window::scroll_callback(GLFWwindow* win, double xoffset,
                                  double yoffset) {
    auto* this_window = (window*)glfwGetWindowUserPointer(win);
    this_window->m_scroll_callback(win, xoffset, yoffset);
}

void ore::window::mouse_button_callback(GLFWwindow* win, int button, int action,
                                        int mods) {
    auto* this_window = (window*)glfwGetWindowUserPointer(win);
    this_window->m_mouse_button_callback(win, button, action, mods);
}

void ore::window::reshape_callback(GLFWwindow* win, int x, int y) {
    auto* this_window = (window*)glfwGetWindowUserPointer(win);
    this_window->win_x = x;
    this_window->win_y = y;
    this_window->m_reshape_callback(win, x, y);
}

GLFWwindow* ore::window::get_window() const { return m_window; }

template <typename Lambda>
void ore::window::set_key_callback(Lambda&& callback) {
    m_key_callback = std::forward<Lambda>(callback);
    glfwSetKeyCallback(m_window, key_callback);
}

template <typename Lambda>
void ore::window::set_mouse_position_callback(Lambda&& callback) {
    m_mouse_pos_callback = std::forward<Lambda>(callback);
    glfwSetCursorPosCallback(m_window, mouse_pos_callback);
}

template <typename Lambda>
void ore::window::set_mouse_scroll_callback(Lambda&& callback) {
    m_scroll_callback = std::forward<Lambda>(callback);
    glfwSetScrollCallback(m_window, scroll_callback);
}

template <typename Lambda>
void ore::window::set_mouse_button_callback(Lambda&& callback) {
    m_mouse_button_callback = std::forward<Lambda>(callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
}

template <typename Lambda>
void ore::window::set_window_reshape_callback(Lambda&& callback) {
    m_reshape_callback = std::forward<Lambda>(callback);
    glfwSetFramebufferSizeCallback(m_window, reshape_callback);
}

ore::window::~window() { stop(); }
