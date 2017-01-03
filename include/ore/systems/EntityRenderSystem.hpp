#ifndef ENTITY_RENDER_SYSTEM_H
#define ENTITY_RENDER_SYSTEM_H

#define _USE_MATH_DEFINES

#include <ore/components/ModelComponent.hpp>
#include <ore/components/Position3DComponent.hpp>
#include <ore/systems/System.hpp>
#include <ore/Entity.hpp>

#include <glm/ext.hpp>
#include <vector>

namespace ore {
    class EntityRenderSystem : public System<ModelComponent, Position3DComponent> {

    };
}

#endif
