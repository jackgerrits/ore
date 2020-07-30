#pragma once



#include <ore/components/component.hpp>

#include <glm/ext.hpp>

namespace ore {
    struct light_component : public base_component<light_component>{
        glm::vec4 position;     // Position of the camera in world coordinates. w value of 0 indicates directional light, 1 indicates positional/point light
        glm::vec3 specular;     // Colour intensities of each light component
        glm::vec3 diffuse;
        glm::vec3 ambient;
        float radius;           // Radius used for attenuation
        float coneAngle;        // Angle and direction of cone for spotlights
        glm::vec3 coneDirection;

        virtual std::string get_type() const {
            return "light";
        }
    };
}
