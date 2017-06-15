#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#define _USE_MATH_DEFINES

#include <ore/components/Component.hpp>
#include <ore/Model.hpp>

#include <glm/ext.hpp>
#include <vector>
#include <memory>

namespace ore {
     class ModelComponent : public BaseComponent<ModelComponent> {
    public:
        ModelComponent(std::shared_ptr<Model> model) :
            model(model)
        {}

        std::shared_ptr<Model> model;

        virtual std::string getType() const {
            return "model";
        }
    };
}

#endif
