#pragma once

#include <ore/components/camera_component.h>
#include <ore/components/light_component.h>
#include <ore/components/model_component.h>
#include <ore/components/position_3d_component.h>
#include <ore/entity.h>
#include <ore/entity_manager.h>
#include <ore/shaders/entity_shader.h>

#include <glm/ext.hpp>
#include <map>
#include <vector>

#include "basic_shader.h"
#include "ore/systems/system.h"

namespace ore {
class basic_render_system : public system {
   public:
    void process(entity_manager& entityManager) override {
        shader.enable();
        glEnableVertexAttribArray(0);

        for (const auto& entity : entityManager.query<model_component>()) {
            auto model =
                entity->get_component<model_component>()->m_model.get();

            for (const auto& part : model->get_model_parts()) {
                glBindVertexArray(part.get_vao_id());
                glDrawElements(GL_TRIANGLES, part.get_index_count(),
                               GL_UNSIGNED_INT, (void*)0);
                glBindVertexArray(0);
            }
        }

        glDisableVertexAttribArray(0);
        shader.disable();
    }

   private:
    basic_shader shader;
};
}  // namespace ore
