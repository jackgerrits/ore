#pragma once

#include <cassert>
#include <glad/glad.h>
#include <ore/components/component.h>

#include <glm/ext.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ore {

class entity {
   public:
    entity() = default;
    template <typename T, typename... Args>
    void assign_components(std::unique_ptr<T>&& component, Args... rest);

    template <typename T>
    void assign_components(std::unique_ptr<T>&& component);

    template <typename T>
    void assign_component(std::unique_ptr<T>&& component);

    template <typename T, typename... Args>
    void emplace_component(Args&&... args) {
        static_assert(std::is_base_of<ore::component, T>::value,
                      "T must be a descendant of component");

        components[componentId<T>()] =
            std::make_unique<T>(std::forward<Args>(args)...);
        //            components[componentId<T>()] = new
        //            T(std::forward<Args>(args)...);
    }

    template <typename T>
    bool has_component();

    template <typename T, typename... Args>
    bool has_components();

    template <bool b = true>
    bool has_components() {
        return b;
    }

    template <typename T>
    T* get_component();

    std::vector<component*> get_components();

    virtual ~entity() = default;

   protected:
    std::map<int, std::unique_ptr<component>> components;
};

template <typename T>
void entity::assign_component(std::unique_ptr<T>&& component) {
    static_assert(std::is_base_of<ore::component, T>::value,
                  "T must be a descendant of component");

    components[componentId<T>()] = std::move(component);
}

template <typename T>
bool entity::has_component() {
    return components.count(componentId<T>()) > 0;
}

template <typename T, typename... Args>
bool entity::has_components() {
    return has_component<T>() && has_components<Args...>();
}

template <typename T>
T* entity::get_component() {
    return dynamic_cast<T*>(components[componentId<T>()].get());
}

// TODO Implement remove component

template <typename T, typename... Args>
void entity::assign_components(std::unique_ptr<T>&& component, Args... rest) {
    assign_component(std::move(component));
    assign_components(rest...);
}

template <typename T>
void entity::assign_components(std::unique_ptr<T>&& component) {
    assign_component(std::move(component));
}
}  // namespace ore
