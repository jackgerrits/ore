#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <functional>

struct GLFWwindow;

namespace ore {
enum class execution_state { continue_running, stop };
struct window {
    window();

    [[nodiscard]] int get_width() const { return win_x; }

    [[nodiscard]] int get_height() const { return win_y; }

    [[nodiscard]] GLFWwindow* get_window() const;

    template <typename Lambda>
    void run_render_loop(Lambda&& callback) {
        while (!glfwWindowShouldClose(m_window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            auto exec_state = callback();
            if (exec_state == ore::execution_state::stop) {
                glfwSetWindowShouldClose(m_window, GLFW_TRUE);
            }

            glFlush();
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

    void stop() {
        if (!m_stopped) {
            m_stopped = true;
            glfwDestroyWindow(m_window);
            glfwTerminate();
        }
    }

    template <typename Lambda>
    void set_key_callback(Lambda&& callback);

    template <typename Lambda>
    void set_mouse_position_callback(Lambda&& callback);

    template <typename Lambda>
    void set_mouse_scroll_callback(Lambda&& callback);

    template <typename Lambda>
    void set_mouse_button_callback(Lambda&& callback);

    template <typename Lambda>
    void set_window_reshape_callback(Lambda&& callback);

    virtual ~window();

   private:
    static void key_callback(GLFWwindow* window, int key, int scancode,
                             int action, int mods);
    static void mouse_pos_callback(GLFWwindow* window, double x, double y);
    static void scroll_callback(GLFWwindow* window, double xoffset,
                                double yoffset);
    static void mouse_button_callback(GLFWwindow* window, int button,
                                      int action, int mods);
    static void reshape_callback(GLFWwindow* window, int x, int y);

    std::function<void(GLFWwindow*, int, int, int, int)> m_key_callback;
    std::function<void(GLFWwindow*, double x, double y)> m_mouse_pos_callback;
    std::function<void(GLFWwindow*, double xoffset, double yoffset)>
        m_scroll_callback;
    std::function<void(GLFWwindow*, int button, int action, int)>
        m_mouse_button_callback;
    std::function<void(GLFWwindow*, int x, int y)> m_reshape_callback;

    int win_x = 640;
    int win_y = 480;
    GLFWwindow* m_window;
    bool m_stopped = false;
};

}  // namespace ore
