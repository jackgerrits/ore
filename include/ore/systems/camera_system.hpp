#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#define _USE_MATH_DEFINES

#include <ore/components/camera_component.hpp>
#include <ore/systems/system.hpp>
#include <ore/entity.hpp>
#include <ore/entity_manager.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

namespace ore {
    // TODO: Add input system to this
    class camera_system : public system {
    public:
        virtual void process(entity_manager& entityManager) {
            // Do something with input.
        }

        void look(entity* camera, glm::vec3 at);
        void look(entity* camera, glm::vec3 from, glm::vec3 at);
    private:

    };
}

#endif
