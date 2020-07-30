#pragma once

#include <ore/components/component.hpp>

#include <memory>
#include <vector>
#include <assert.h>
#include <string>
#include <map>
#include <GL/glew.h>
#include <glm/ext.hpp>

namespace ore {

    class entity {
    public:
        template<typename T, typename... Args>
        void assign_components(T* component, Args... rest);

        template<typename T>
        void assign_components(T* component);

        template<typename T>
        void assign_component(T* component);

        template <typename T>
        bool has_component();

        template<typename T, typename... Args>
        bool has_components();

        template<bool b = true>
        bool has_components() {
            return b;
        }

        template <typename T>
        T* get_component();

        std::vector<component*> get_components();

    protected:
        std::map<int, component*> components;
    };

    template<typename T>
    void entity::assign_component(T* component) {
        static_assert(
            std::is_base_of<ore::component, T>::value,
            "T must be a descendant of component"
        );

        components[componentId<T>()] = component;
    }

    template <typename T>
    bool entity::has_component() {
        return components.count(componentId<T>()) > 0;
    }

    template<typename T, typename... Args>
    bool entity::has_components() {
        return has_component<T>() && has_components<Args...>();
    }

    template <typename T>
    T* entity::get_component() {
        return (T*)components[componentId<T>()];
    }

    // TODO Implement remove component

    template<typename T, typename... Args>
    void entity::assign_components(T* component, Args... rest) {
        assign_component(component);
        assign_components(rest...);
    }

    template<typename T>
    void entity::assign_components(T* component) {
        assign_component(component);
    }
}
