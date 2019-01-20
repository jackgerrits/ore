#include <ore/systems/camera_system.hpp>

#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream>

namespace ore {
    void camera_system::look(entity* camera, glm::vec3 at) {
        glm::vec3 up(0.0f, 1.0f, 0.0f);

        camera_component* cameraComponent = camera->getComponent<camera_component>();
std::cout << cameraComponent << std::endl;
        cameraComponent->view = glm::lookAt(cameraComponent->position, at, up);
        std::cout << glm::to_string(cameraComponent->view) << std::endl;
    }

    void camera_system::look(entity* camera, glm::vec3 from, glm::vec3 at) {
        glm::vec3 up(0.0f, 1.0f, 0.0f);

        camera->getComponent<camera_component>()->view = glm::lookAt(from, at, up);
        std::cout << glm::to_string(camera->getComponent<camera_component>()->view) << std::endl;

    }
}
