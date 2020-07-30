#pragma once



#include <ore/components/model_component.hpp>
#include <ore/components/camera_component.hpp>
#include <ore/components/position_3d_component.hpp>
#include <ore/components/light_component.hpp>
#include <ore/entity.hpp>
#include <ore/entity_manager.hpp>
#include <ore/shaders/entity_shader.hpp>

#include "basic_shader.hpp"

#include "ore/systems/system.hpp"

#include <glm/ext.hpp>
#include <vector>
#include <map>

namespace ore {
    class basic_render_system : public system {

    public:
        virtual void process(entity_manager& entityManager) override {
            shader.enable();
            glEnableVertexAttribArray(0);

            for (auto& entity : entityManager.query<model_component>()) {
                auto model = entity->get_component<model_component>()->m_model.get();

                for (auto& part : model->get_model_parts()) {
                    glBindVertexArray(part.get_vao_id());
                    glDrawElements(GL_TRIANGLES, part.get_index_count(), GL_UNSIGNED_INT, (void*)0);
                    glBindVertexArray(0);
                }
            }

            glDisableVertexAttribArray(0);
            shader.disable();
        }

    private:
        basic_shader shader;
    };
}

