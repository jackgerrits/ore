#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#define _USE_MATH_DEFINES

#include <ore/components/CameraComponent.hpp>
#include <ore/systems/System.hpp>
#include <ore/Entity.hpp>
#include <ore/EntityManager.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

namespace ore {
    // TODO: Add input system to this
    class CameraSystem : public System {
    public:
        virtual void process(EntityManager* entityManager) {
            // Do something with input.
        }

        void look(Entity* camera, glm::vec3 at);
        void look(Entity* camera, glm::vec3 from, glm::vec3 at);
    private:

    };
}

#endif
