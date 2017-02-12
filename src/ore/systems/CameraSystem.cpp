#include <ore/systems/CameraSystem.hpp>

namespace ore {
    void CameraSystem::look(Entity* camera, glm::vec3 at) {
        glm::vec3 up(0.0f, 1.0f, 0.0f);

        CameraComponent* cameraComponent = camera->getComponent<CameraComponent>();
        cameraComponent->view = glm::lookAt(cameraComponent->position, at, up);
        std::cout << glm::to_string(cameraComponent->view) << std::endl;
    }

    void CameraSystem::look(Entity* camera, glm::vec3 from, glm::vec3 at) {
        glm::vec3 up(0.0f, 1.0f, 0.0f);

        camera->getComponent<CameraComponent>()->view = glm::lookAt(from, at, up);
        std::cout << glm::to_string(camera->getComponent<CameraComponent>()->view) << std::endl;

    }
}
