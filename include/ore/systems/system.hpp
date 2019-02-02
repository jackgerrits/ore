#pragma once

#define _USE_MATH_DEFINES

#include <ore/components/component.hpp>
#include <ore/entity.hpp>
#include <ore/entity_manager.hpp>

#include <glm/ext.hpp>
#include <vector>

namespace ore {
    class system {
    public:
        system() {}

        // Systems will always be given a list of all components that fullfil the requirements.
        virtual void process(entity_manager& entityManager) = 0;
    };
}
