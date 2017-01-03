#ifndef SYSTEM_H
#define SYSTEM_H

#define _USE_MATH_DEFINES

#include <ore/components/Component.hpp>
#include <ore/Entity.hpp>

#include <glm/ext.hpp>
#include <vector>

namespace ore {
    // Accepts a variadic template of types and returns a vector of their corresponding ids.
    struct IdTypeResolver {
        template<class T, class... Args>
        std::vector<int> build() {
            contents.push_back(componentId<T>());
            return build<Args...>();
        }

        template<class T>
        std::vector<int> build()
        {
            contents.push_back(componentId<T>());
            return contents;
        }

        std::vector<int> contents;
    };

    template<typename... Args>
    class System {
    public:
        const std::vector<int> requiredComponents;

        System() {
            IdTypeResolver resolver;
            requiredComponents = resolver.build<Args...>();
        }

        // Systems will always be given a list of all components that fullfil the requirements.
        virtual void visit(std::vector<Entity*> entities) {
            for(auto entity : entities) {
                visit(entity);
            }
        }
    };
}

#endif
