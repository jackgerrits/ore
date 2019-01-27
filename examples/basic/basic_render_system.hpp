#pragma once

#define _USE_MATH_DEFINES

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
				auto model = entity->getComponent<model_component>()->model.get();

				for (auto& part : model->getModelParts()) {
					glBindVertexArray(part.getVaoID());
					glDrawElements(GL_TRIANGLES, part.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
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
