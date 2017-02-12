#ifndef SYSTEM_H
#define SYSTEM_H

#define _USE_MATH_DEFINES

#include <ore/components/Component.hpp>
#include <ore/Entity.hpp>
#include <ore/EntityManager.hpp>

#include <glm/ext.hpp>
#include <vector>

namespace ore {
    class System {
    public:
        System() {
        }

        // Systems will always be given a list of all components that fullfil the requirements.
        virtual void process(EntityManager* entityManager) = 0;
    };
}

#endif
