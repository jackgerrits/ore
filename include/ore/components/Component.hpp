#ifndef COMPONENT_H
#define COMPONENT_H

#define _USE_MATH_DEFINES

#include <string>

namespace ore {

    // Generates a unique integer for each different type that it is called with.
    static int currentComponentId = 0;
    template <typename T>
    int componentId() {
        static int id = currentComponentId++;
        return id;
    }

    // Base abstract component to be used in Entity.
    struct Component {
        virtual int getId() = 0;
    };

    // All components must inherit from BaseComponent to
    // properly initialise the id.
    template <typename T>
    struct BaseComponent : public Component {
        static struct ThreadsafeId {
            int id;
            ThreadsafeId() { id = componentId<T>(); }
        } _;
      virtual int getId() { return _.id; }
    };

    template <typename T>
    typename BaseComponent<T>::ThreadsafeId BaseComponent<T>::_;
}

#endif
