#pragma once

#include <ore/components/component.h>
#include <ore/model.h>

#include <glm/ext.hpp>
#include <memory>
#include <utility>
#include <vector>

namespace ore {
class model_component : public base_component<model_component> {
   public:
    explicit model_component(std::shared_ptr<model> model) : m_model(std::move(model)) {}

    std::shared_ptr<model> m_model;

    [[nodiscard]] std::string get_type() const override { return "model"; }
};
}  // namespace ore
