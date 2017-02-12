#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#define _USE_MATH_DEFINES

#include <ore/Entity.hpp>

#include <memory>
#include <assert.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/ext.hpp>

namespace ore {

    class EntityManager {
    public:
        std::vector<Entity*> entities;
    public:
        template<typename... Args>
        std::vector<Entity*> query() {
            std::vector<Entity*> found;
            for(auto entity : entities) {
                if(entity->hasComponents<Args...>()) {
                    found.push_back(entity);
                }
            }

            return found;
        }

        template<typename... Args>
        Entity* newEntity(Args... components) {
            Entity* entity = new Entity();
            entity->assignComponents(components...);
            entities.push_back(entity);

            return entity;
        }

        Entity* newEntity() {
            Entity* entity = new Entity();
            entities.push_back(entity);

            return entity;
        }

        void kill(Entity* entity) {
            // TODO Remove entity from vector.
        }
    };
}

#endif
