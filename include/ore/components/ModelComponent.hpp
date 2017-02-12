#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#define _USE_MATH_DEFINES

#include <ore/components/Component.hpp>
#include <ore/Model.hpp>

#include <glm/ext.hpp>
#include <vector>

namespace ore {
    struct ModelComponent : public BaseComponent<ModelComponent> {
        std::shared_ptr<Model> model;

        ModelComponent(std::shared_ptr<Model> model);
    };

    ModelComponent::ModelComponent(std::shared_ptr<Model> model) {
        this->model = model;
    }
}

#endif
