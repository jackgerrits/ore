#pragma once

#define _USE_MATH_DEFINES

#include <ore/components/component.hpp>
#include <ore/model.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

namespace ore {
    class camera_component : public base_component<camera_component> {
    public:
        glm::vec3 position;
        glm::vec3 focalPoint;

        glm::mat4 view;
        glm::mat4 projection;

        camera_component() {}

        virtual std::string getType() const {
            return "camera";
        }

        // CameraComponent(glm::vec3 position, glm::vec3 focalPoint, glm::mat4 projection)
        //     : position(position), focalPoint(focalPoint), projection(projection) {}
    };
}