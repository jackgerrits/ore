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

#include "resource_path.h"

using namespace std;
using namespace ore;
using namespace glm;

int winX = 1024;
int winY = 768;

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

GLFWwindow* initialise() {
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}


int main() {
    auto window = initialise();

    ore::entity_manager em;
    auto e = em.newEntity(new ore::position_3d_component());

    auto camera = em.newEntity();
    auto light = em.newEntity();

    ore::camera_system cs;
    ore::entity_render_system ers;

    auto p3d = e->getComponent<position_3d_component>();
    p3d->position = { 0.f, 0.f, 0.f};
    p3d->scale = { 50,50,50 };

    auto barrel = loader::getLoader().loadModel(BARREL_RES_DIR "/Barrel/Barrel02.obj");

    e->assignComponent(new model_component(barrel));

    auto lc = new light_component();
    lc->specular = vec3(1.0f, 1.0f, 1.0f);
    lc->diffuse = vec3(0.7f, 0.7f, 0.7f);
    lc->ambient = vec3(0.1f, 0.1f, 0.1f);
    lc->position = vec4{ 10.0f, 10.0f, 2.0f, 1.0f };
    lc->radius = 50.0f;
    light->assignComponent(lc);

    auto cc = new camera_component();
    cc->position = vec4(0.0f, 3.0f, 3.0f, 0.0f);
    cc->projection = glm::perspective(M_PI/4.0, static_cast<double>(winX) / static_cast<double>(winY), 1.0, 100.0);
    camera->assignComponent(cc);
    cs.look(camera, vec3(1.f, 1.0f, 0.0f));

    // Main logic/render loop.
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        ers.process(em);
        glFlush();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
