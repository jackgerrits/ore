#ifndef ENTITY_RENDER_SYSTEM_H
#define ENTITY_RENDER_SYSTEM_H

#define _USE_MATH_DEFINES

#include <ore/components/model_component.hpp>
#include <ore/components/camera_component.hpp>
#include <ore/components/position_3d_component.hpp>
#include <ore/components/light_component.hpp>
#include <ore/entity.hpp>
#include <ore/entity_manager.hpp>
#include <ore/shaders/entity_shader.hpp>


#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <map>
#include <iostream>


namespace ore {
    class entity_render_system {

    public:
        std::map<model*, std::vector<entity*>> obtainModelEntityMapping(entity_manager* entityManager) {
            std::map<model*, std::vector<entity*>> modelMappings;

            for(auto& entity : entityManager->query<position_3d_component, ModelComponent>()) {
                model* model = entity->getComponent<ModelComponent>()->model.get();

                if(modelMappings.count(model) == 0) {
                    modelMappings[model] = std::vector<ore::entity*>();
                }

                modelMappings[model].push_back(entity);
            }

            return modelMappings;
        }

        // Render order. Sort models, load lights, render entities in groups by model.
        virtual void process(entity_manager* entityManager) {

            // Construct a map of models so that data only needs to be loaded once per pass.
            auto modelMappings = obtainModelEntityMapping(entityManager);

            camera_component* camera = entityManager->query<camera_component>()[0]->getComponent<camera_component>();

            shader.enable();
            shader.loadProjection(camera->projection);
            shader.loadLights(entityManager->query<light_component>());
            std::cout << "nums found: "<< entityManager->query<light_component>().size() << std::endl;
            for(auto l : entityManager->query<light_component>()) {
                std::cout << glm::to_string(l->getPosition()) << std::endl;
                // std::cout << l->getType() << std::endl;
                std::cout << l->hasComponent<light_component>() << std::endl;

            }
            shader.loadView(camera->view);

            std::cout << ">>"<< entityManager->entities.size() << std::endl;

            // std::cout << glm::to_string(camera->view) << std::endl;

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            for(auto& kv : modelMappings) {
                for(auto& part : kv.first->getModelParts()) {
                    shader.loadModelPart(part);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, part.getTextureID());
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                    glBindVertexArray(part.getVaoID());

                    for(auto& entity : kv.second) {
                        shader.loadEntity(entity);

                        glDrawElements(GL_TRIANGLES, part.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
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
}

#endif
