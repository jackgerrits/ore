#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#define _USE_MATH_DEFINES

#include <ore/Component.hpp>

#include <glm/ext.hpp>
#include <vector>

namespace ore {
    class Position3DComponent : public BaseComponent<Position3DComponent> {
    public:
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;

        Position3DComponent();
    };

    Position3DComponent::Position3DComponent() {
        // Register this component to have an id.
        Component::id = id<Position3DComponent>();

        position = glm::vec3(0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
        rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    }
}

#endif