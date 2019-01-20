#ifndef MATERIAL_H
#define MATERIAL_H

#include <ore/lib/tiny_obj_loader.h>

#include <array>

namespace ore {
    class material {
    public:
        std::string name;

        std::array<float, 3> ambient;
        std::array<float, 3> diffuse;
        std::array<float, 3> specular;
        std::array<float, 3> transmittance;
        std::array<float, 3> emission;

        float shininess;

        std::string ambientTexture;             // map_Ka
        std::string diffuseTexture;             // map_Kd
        std::string specularTexture;            // map_Ks
        std::string specularHighlightTexture;   // map_Ns
        std::string bumpTexture;                // map_bump, bump
        std::string displacementTexture;        // disp
        std::string alphaTexture;               // map_d

        material();
        material(tinyobj::material_t);
    };
}

#endif
