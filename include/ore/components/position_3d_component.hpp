#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#define _USE_MATH_DEFINES

#include <ore/components/Component.hpp>

#include <glm/ext.hpp>
#include <vector>

namespace ore {
    class Position3DComponent : public base_component<Position3DComponent> {
    public:
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;

        Position3DComponent() :
            position(glm::vec3(0.0f, 0.0f, 0.0f)),
            scale(glm::vec3(1.0f, 1.0f, 1.0f)),
            rotation(glm::vec3(0.0f, 0.0f, 0.0f))
        {}

        virtual std::string getType() const {
            return "position";
        }
    };
}

#endif
