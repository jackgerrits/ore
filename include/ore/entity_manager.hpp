#pragma once

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
                if(entity->has_components<Args...>()) {
                    found.push_back(entity);
                }
            }

            return found;
        }

        template<typename... Args>
        entity* new_entity(Args... components) {
            entity* new_entity = new entity();
            new_entity->assign_components(components...);
            entities.push_back(new_entity);

            return new_entity;
        }

        entity* new_entity() {
            entity* entity = new ore::entity();
            entities.push_back(entity);

            return entity;
        }

        void kill(entity* entity) {
            // TODO Remove entity from vector.
        }
    };
}
