#ifndef ENTITY_H
#define ENTITY_H

#define _USE_MATH_DEFINES

#include <ore/Model.hpp>
#include <ore/components/Component.hpp>

#include <memory>
#include <assert.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/ext.hpp>

namespace ore {

    class Entity {
    protected:
        std::shared_ptr<Model> model;

        glm::vec3 position;
        glm::vec3 scale;
        float xRot;
        float yRot;
        float zRot;

        std::map<int, Component*> components;
    public:
        Entity(std::shared_ptr<Model> model);
        Entity();

        template<typename T>
        void assignComponent(T* component);

        template <typename T>
        bool hasComponent();

        template <typename T>
        T getComponent();


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
    };

    template<typename T>
    void Entity::assignComponent(T* component){
        static_assert(
            std::is_base_of<Component, T>::value,
            "T must be a descendant of Component"
        );

        components[componentId<component>()] = component;
    }

    template <typename T>
    bool Entity::hasComponent() {
        return components.count(componentId<T>()) > 0;
    }

    template <typename T>
    T Entity::getComponent() {
        return (T*)components[componentId<T>()];
    }
}

#endif
