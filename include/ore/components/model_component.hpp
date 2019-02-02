#pragma once



#include <ore/components/Component.hpp>
#include <ore/model.hpp>

#include <glm/ext.hpp>
#include <vector>
#include <memory>

namespace ore {
     class model_component : public base_component<model_component> {
    public:
        model_component(std::shared_ptr<model> model) :
            model(model)
        {}

        std::shared_ptr<model> model;

        virtual std::string get_type() const {
            return "model";
        }
    };
}
