#pragma once

#define _USE_MATH_DEFINES

#include <string>

namespace ore {

    // Generates a unique integer for each different type that it is called with.
    extern int currentComponentId;
    template <typename T>
    int componentId() {
        static int id = ++currentComponentId;
        return id;
    }

    // Base abstract component to be used in entity.
    struct Component {
        virtual int getId() = 0;

        virtual std::string getType() const {
            return "unset";
        }
    };

    // All components must inherit from BaseComponent to
    // properly initialise the id.
    template <typename T>
    struct base_component : public Component {
        static struct ThreadsafeId {
            int id;
            ThreadsafeId() { id = componentId<T>(); }
        } _;
      virtual int getId() { return _.id; }
    };

    template <typename T>
    typename base_component<T>::ThreadsafeId base_component<T>::_;
}
