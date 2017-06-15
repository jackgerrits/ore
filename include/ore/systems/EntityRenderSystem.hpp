#ifndef ENTITY_RENDER_SYSTEM_H
#define ENTITY_RENDER_SYSTEM_H

#define _USE_MATH_DEFINES

#include <ore/components/ModelComponent.hpp>
#include <ore/components/CameraComponent.hpp>
#include <ore/components/Position3DComponent.hpp>
#include <ore/components/LightComponent.hpp>
#include <ore/Entity.hpp>
#include <ore/EntityManager.hpp>
#include <ore/shaders/EntityShader.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <map>
#include <iostream>


namespace ore {
    class EntityRenderSystem {

    public:
        std::map<Model*, std::vector<Entity*>> obtainModelEntityMapping(EntityManager* entityManager) {
            std::map<Model*, std::vector<Entity*>> modelMappings;

            for(auto& entity : entityManager->query<Position3DComponent, ModelComponent>()) {
                Model* model = entity->getComponent<ModelComponent>()->model.get();

                if(modelMappings.count(model) == 0) {
                    modelMappings[model] = std::vector<Entity*>();
                }

                modelMappings[model].push_back(entity);
            }

            return modelMappings;
        }

        // Render order. Sort models, load lights, render entities in groups by model.
        virtual void process(EntityManager* entityManager) {

            // Construct a map of models so that data only needs to be loaded once per pass.
            auto modelMappings = obtainModelEntityMapping(entityManager);

            CameraComponent* camera = entityManager->query<CameraComponent>()[0]->getComponent<CameraComponent>();

            shader.enable();
            shader.loadProjection(camera->projection);
            shader.loadLights(entityManager->query<LightComponent>());
            std::cout << entityManager->query<LightComponent>().size() << std::endl;
            for(auto l : entityManager->query<LightComponent>()) {
                std::cout << glm::to_string(l->getPosition()) << std::endl;
                // std::cout << l->getType() << std::endl;
                std::cout << l->hasComponent<LightComponent>() << std::endl;

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
                }
            }

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
            glBindVertexArray(0);
            shader.disable();
        }

    private:
        EntityShader shader;
    };
}

#endif
