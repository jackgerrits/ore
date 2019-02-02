#pragma once

#include <ore/components/Component.hpp>

#include <memory>
#include <vector>
#include <assert.h>
#include <string>
#include <iostream>
#include <map>
#include <GL/glew.h>
#include <glm/ext.hpp>

namespace ore {

    class entity {
    public:
        template<typename T, typename... Args>
        void assignComponents(T* component, Args... rest);

        template<typename T>
        void assignComponents(T* component);

        template<typename T>
        void assignComponent(T* component);

        template <typename T>
        bool hasComponent();

        template<typename T, typename... Args>
        bool hasComponents();

        template<bool b = true>
        bool hasComponents() {
            return b;
        }

        template <typename T>
        T* getComponent();

        std::vector<Component*> getComponents();

    protected:
        std::map<int, Component*> components;
    };

    template<typename T>
    void entity::assignComponent(T* component) {
        static_assert(
            std::is_base_of<Component, T>::value,
            "T must be a descendant of Component"
        );

        components[componentId<T>()] = component;
    }

    template <typename T>
    bool entity::hasComponent() {
        return components.count(componentId<T>()) > 0;
    }

    template<typename T, typename... Args>
    bool entity::hasComponents() {
        return hasComponent<T>() && hasComponents<Args...>();
    }

    template <typename T>
    T* entity::getComponent() {
        return (T*)components[componentId<T>()];
    }

    // TODO Implement remove component

    template<typename T, typename... Args>
    void entity::assignComponents(T* component, Args... rest) {
        assignComponent(component);
        assignComponents(rest...);
    }

    template<typename T>
    void entity::assignComponents(T* component) {
        assignComponent(component);
    }
}
