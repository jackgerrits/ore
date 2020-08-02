#pragma once

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
struct component {
    virtual int getId() = 0;

    [[nodiscard]] virtual std::string get_type() const { return "unset"; }

    virtual ~component() = default;
};

// All components must inherit from BaseComponent to
// properly initialise the id.
template <typename T>
struct base_component : public component {
    static struct thread_safe_id {
        int id;
        thread_safe_id() { id = componentId<T>(); }
    } _;
    int getId() override { return _.id; }
};

template <typename T>
typename base_component<T>::thread_safe_id base_component<T>::_;
}  // namespace ore
