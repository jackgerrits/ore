#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#define _USE_MATH_DEFINES

#include <ore/components/Component.hpp>
#include <ore/Model.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

namespace ore {
    class CameraComponent : public BaseComponent<CameraComponent> {
    public:
        glm::vec3 position;
        glm::vec3 focalPoint;

        glm::mat4 view;
        glm::mat4 projection;

        CameraComponent() {}

        virtual std::string getType() const {
            return "camera";
        }

        // CameraComponent(glm::vec3 position, glm::vec3 focalPoint, glm::mat4 projection)
        //     : position(position), focalPoint(focalPoint), projection(projection) {}
    };
}

#endif
