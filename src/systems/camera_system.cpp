#include <ore/systems/camera_system.hpp>

#include <glm/ext.hpp>

namespace ore {
    void camera_system::look(entity* camera, glm::vec3 at) {
        glm::vec3 up(0.0f, 1.0f, 0.0f);
        auto cameraComponent = camera->getComponent<camera_component>();
        cameraComponent->view = glm::lookAt(cameraComponent->position, at, up);
    }

    void camera_system::look(entity* camera, glm::vec3 from, glm::vec3 at) {
        glm::vec3 up(0.0f, 1.0f, 0.0f);
        camera->getComponent<camera_component>()->view = glm::lookAt(from, at, up);
    }
}
