#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#define _USE_MATH_DEFINES

#include <ore/components/Component.hpp>

#include <glm/ext.hpp>
#include <vector>

namespace ore {
    class position_3d_component : public base_component<position_3d_component> {
    public:
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;

        position_3d_component() :
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
