#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#define _USE_MATH_DEFINES

#include <ore/components/Component.hpp>
#include <ore/model.hpp>

#include <glm/ext.hpp>
#include <vector>
#include <memory>

namespace ore {
     class ModelComponent : public base_component<ModelComponent> {
    public:
        ModelComponent(std::shared_ptr<model> model) :
            model(model)
        {}

        std::shared_ptr<model> model;

        virtual std::string getType() const {
            return "model";
        }
    };
}

#endif
