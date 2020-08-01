#pragma once

#include <ore/components/component.h>
#include <ore/entity.h>
#include <ore/entity_manager.h>

#include <glm/ext.hpp>
#include <vector>

namespace ore {
class system {
   public:
    system() = default;

    // Systems will always be given a list of all components that fullfil the
    // requirements.
    virtual void process(entity_manager& entityManager) = 0;
};
}  // namespace ore
