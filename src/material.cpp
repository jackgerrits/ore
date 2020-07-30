#include <ore/material.hpp>

using namespace ore;

material::material() {
    name = "default";
    ambient.fill(1.f);
    diffuse.fill(1.f);
    specular.fill(1.f);
    transmittance.fill(0.f);
    emission.fill(0.f);

    shininess = 0;
}

material::material(tinyobj::material_t material) {
    name = material.name;
    std::copy(std::begin(material.ambient), std::end(material.ambient), ambient.begin());
    std::copy(std::begin(material.diffuse), std::end(material.diffuse), diffuse.begin());
    std::copy(std::begin(material.specular), std::end(material.specular), specular.begin());
    std::copy(std::begin(material.transmittance), std::end(material.transmittance), transmittance.begin());
    std::copy(std::begin(material.emission), std::end(material.emission), emission.begin());

    shininess = material.shininess;

    ambientTexture = material.ambient_texname;
    diffuseTexture = material.diffuse_texname;
    specularTexture = material.specular_texname;
    specularHighlightTexture = material.specular_highlight_texname;
    bumpTexture = material.bump_texname;
    displacementTexture = material.displacement_texname;
    alphaTexture = material.alpha_texname;
}
