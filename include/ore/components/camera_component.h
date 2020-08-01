#pragma once

#include <ore/components/component.h>
#include <ore/model.h>

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace ore {
class camera_component : public base_component<camera_component> {
   public:
    glm::vec3 position;
    glm::vec3 focalPoint;

    glm::mat4 view;
    glm::mat4 projection;

    camera_component() {}

    virtual std::string get_type() const { return "camera"; }

    // CameraComponent(glm::vec3 position, glm::vec3 focalPoint, glm::mat4
    // projection)
    //     : position(position), focalPoint(focalPoint), projection(projection)
    //     {}
};
}  // namespace ore
