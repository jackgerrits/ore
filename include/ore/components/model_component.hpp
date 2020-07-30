#pragma once



#include <ore/components/component.hpp>
#include <ore/model.hpp>

#include <glm/ext.hpp>
#include <vector>
#include <memory>

namespace ore {
     class model_component : public base_component<model_component> {
    public:
        model_component(std::shared_ptr<model> model) :
                m_model(model)
        {}

        std::shared_ptr<model> m_model;

        virtual std::string get_type() const {
            return "model";
        }
    };
}
