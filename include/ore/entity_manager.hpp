#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#define _USE_MATH_DEFINES

#include <ore/entity.hpp>

#include <memory>
#include <assert.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/ext.hpp>

namespace ore {

    class entity_manager {
    public:
        std::vector<entity*> entities;
    public:
        template<typename... Args>
        std::vector<entity*> query() {
            std::vector<entity*> found;
            for(auto entity : entities) {
                if(entity->hasComponents<Args...>()) {
                    found.push_back(entity);
                }
            }

            return found;
        }

        template<typename... Args>
        entity* newEntity(Args... components) {
            entity* new_entity = new entity();
            new_entity->assignComponents(components...);
            entities.push_back(new_entity);

            return new_entity;
        }

        entity* newEntity() {
            entity* entity = new ore::entity();
            entities.push_back(entity);

            return entity;
        }

        void kill(entity* entity) {
            // TODO Remove entity from vector.
        }
    };
}

#endif
