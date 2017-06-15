#ifndef ENTITY_H
#define ENTITY_H

#define _USE_MATH_DEFINES

#include <ore/Model.hpp>
#include <ore/components/Component.hpp>

#include <memory>
#include <vector>
#include <assert.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/ext.hpp>

namespace ore {

    class Entity {
    public:
        Entity(std::shared_ptr<Model> model);
        Entity();

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

        virtual bool update();

        std::shared_ptr<Model> getModel() const;
        glm::mat4 getModelMatrix();

        glm::vec3 getPosition() const;
        glm::vec3 getScale() const;
        float getRotationX() const;
        float getRotationY() const;
        float getRotationZ() const;

        glm::vec3 getDirectionVector();

        // Can be overriden in inheriting class if behaviour requires it.
        // Set the value absolutely of position, scale, or rotation.
        virtual void setPosition(glm::vec3);
        virtual void placeBottomEdge(float surfaceY);
        virtual void setScale(glm::vec3);
        virtual void setRotationX(float);
        virtual void setRotationY(float);
        virtual void setRotationZ(float);


        // Set the value of rotation or position relatively (Takes into account current value)
        virtual void rotateX(float);
        virtual void rotateY(float);
        virtual void rotateZ(float);
        virtual void move(glm::vec3);

        // Generates the transformation to be applied to the mesh with the given parameters.
        static glm::mat4 calculateModelMatrix(glm::vec3 position, glm::mat4 rotation, glm::vec3 scale);
        static glm::mat4 calculateRotationMatrix(float xRot, float yRot, float zRot);

    protected:
        std::shared_ptr<Model> model;

        glm::vec3 position;
        glm::vec3 scale;
        float xRot;
        float yRot;
        float zRot;

        std::map<int, Component*> components;
    };

    template<typename T>
    void Entity::assignComponent(T* component) {
        static_assert(
            std::is_base_of<Component, T>::value,
            "T must be a descendant of Component"
        );

        components[componentId<T>()] = component;
    }

    template <typename T>
    bool Entity::hasComponent() {
        return components.count(componentId<T>()) > 0;
    }

    template<typename T, typename... Args>
    bool Entity::hasComponents() {
        return hasComponent<T>() && hasComponents<Args...>();
    }

    template <typename T>
    T* Entity::getComponent() {
        return (T*)components[componentId<T>()];
    }

    // TODO remove component

    template<typename T, typename... Args>
    void Entity::assignComponents(T* component, Args... rest) {
        assignComponent(component);
        assignComponents(rest...);
    }

    template<typename T>
    void Entity::assignComponents(T* component) {
        assignComponent(component);
    }
}

#endif
