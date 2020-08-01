#pragma once

#include <ore/components/camera_component.h>
#include <ore/components/light_component.h>
#include <ore/components/model_component.h>
#include <ore/components/position_3d_component.h>
#include <ore/entity.h>
#include <ore/entity_manager.h>
#include <ore/shaders/entity_shader.h>
#include <ore/systems/system.h>

#include <glm/ext.hpp>
#include <iostream>
#include <map>
#include <vector>

namespace ore {
class entity_render_system : ore::system {
   public:
    std::map<model*, std::vector<entity*>> get_model_entity_mapping(
        entity_manager& entityManager) {
        std::map<model*, std::vector<entity*>> modelMappings;

        for (auto& entity :
             entityManager.query<position_3d_component, model_component>()) {
            model* model =
                entity->get_component<model_component>()->m_model.get();

            if (modelMappings.count(model) == 0) {
                modelMappings[model] = std::vector<ore::entity*>();
            }

            modelMappings[model].push_back(entity);
        }

        return modelMappings;
    }

    // Render order. Sort models, load lights, render entities in groups by
    // model.
    virtual void process(entity_manager& entityManager) override {
        // Construct a map of models so that data only needs to be loaded once
        // per pass.
        auto modelMappings = get_model_entity_mapping(entityManager);

        auto camera = entityManager.query<camera_component>()[0]
                          ->get_component<camera_component>();

        shader.enable();
        shader.load_projection(camera->projection);
        shader.load_lights(entityManager.query<light_component>());
        shader.load_view(camera->view);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        for (auto& kv : modelMappings) {
            for (auto& part : kv.first->get_model_parts()) {
                shader.load_model_part(part);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, part.get_texture_id());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                glBindVertexArray(part.get_vao_id());

                for (auto& entity : kv.second) {
                    shader.load_entity(entity);

                    glDrawElements(GL_TRIANGLES, part.get_index_count(),
                                   GL_UNSIGNED_INT, (void*)0);
                }

                glBindVertexArray(0);
            }
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindVertexArray(0);
        shader.disable();
    }

   private:
    entity_shader shader;
};
}  // namespace ore
