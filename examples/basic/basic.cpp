#include <ore/components/position_3d_component.hpp>
#include <ore/components/light_component.hpp>
#include <ore/components/model_component.hpp>
#include <ore/components/camera_component.hpp>

#include <ore/systems/camera_system.hpp>
#include <ore/systems/entity_render_system.hpp>

#include <ore/entity.hpp>
#include <ore/loader.hpp>
#include <ore/entity_manager.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <memory>

#include "resource_path.h"
#include "basic_render_system.hpp"

using namespace std;
using namespace ore;
using namespace glm;

int winX = 1024;
int winY = 768;

GLFWwindow* initialise(){
    if (!glfwInit()) {
        throw std::runtime_error("glfwInit() failed");
    }

    // Specify that we want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window and OpenGL context
    GLFWwindow* window = glfwCreateWindow(winX, winY, "Basic Example", NULL, NULL);
    if (!window) {
        throw std::runtime_error("glfwCreateWindow() failed");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("glewInit() failed");
    }

    glfwGetFramebufferSize(window, &winX, &winY);

    // Sets the (background) colour for each time the frame-buffer is cleared
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    return window;
}

int main() {
    auto window = initialise();

    ore::entity_manager em;
    auto e = em.new_entity();

    std::vector<float> vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    auto vao = loader::get().load_vao(vertices, indices);
    auto m = std::make_shared<ore::model>();
    m->addModelPart(model_part(vao, indices.size(), 0));
    e->assign_component(new model_component(m));

    basic_render_system brs;

    // Main logic/render loop.
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Prcoess the entities with the render system.
        brs.process(em);

        glFlush();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
