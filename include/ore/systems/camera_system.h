#pragma once

#include <ore/components/camera_component.h>
#include <ore/entity.h>
#include <ore/entity_manager.h>
#include <ore/systems/system.h>

#include <glm/ext.hpp>
#include <glm/glm.hpp>
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
}  // namespace ore
