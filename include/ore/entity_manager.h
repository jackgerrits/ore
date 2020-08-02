#pragma once

#include <assert.h>
#include <glad/glad.h>
#include <ore/entity.h>

#include <glm/ext.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace ore {

class entity_manager {
   public:
    std::vector<std::unique_ptr<entity>> entities;

   public:
    template <typename... Args>
    std::vector<entity*> query() {
        std::vector<entity*> found;
        for (auto& entity : entities) {
            if (entity->has_components<Args...>()) {
                found.push_back(entity.get());
            }
        }

        return found;
    }

    template <typename... Args>
    std::vector<std::tuple<Args*...>>  query_components() {
        std::vector<std::tuple<Args*...>> found;
        for (auto& entity : entities) {
            if (entity->has_components<Args...>()) {
                found.push_back(entity->get_component_list<Args...>());
            }
        }

        return found;
    }

    template <typename... Args>
    entity* new_entity(Args&&... components) {
        auto new_entity = std::make_unique<entity>();
        new_entity->assign_components(std::forward<Args>(components)...);
        auto* entity_ptr = new_entity.get();
        entities.push_back(std::move(new_entity));

        return entity_ptr;
    }

    entity* new_entity() {
        entities.emplace_back(std::make_unique<entity>());
        return entities.back().get();
    }

    void kill(entity* entity) {
        // TODO Remove entity from vector.
    }
};
}  // namespace ore
