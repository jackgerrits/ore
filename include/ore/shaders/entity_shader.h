#pragma once

#include <ore/entity.h>
#include <ore/model.h>
#include <ore/shaders/shader_program.h>

#include <cstdio>
#include <fstream>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "base_dir.h"

namespace ore {
// TODO: Determine better way to reference shaders that isn't relative to
// current directory.
const std::string ENTITY_VERTEX_SHADER = PROJECT_DIR "src/shaders/entity.vert";
const std::string ENTITY_FRAGMENT_SHADER =
    PROJECT_DIR "src/shaders/entity.frag";

class entity_shader : public shader_program {
   public:
    entity_shader();

    virtual void bind_uniform_locations();

    void load_lights(std::vector<entity*> lights);
    void load_light(entity* light, size_t i);
    void load_view(glm::mat4 view);
    void load_entity(entity* entity);
    void load_model_part(const model_part& component);
    void load_projection(glm::mat4 proj);

   private:
    GLuint location_texMap;
    GLuint location_cubeMap;

    GLuint location_projection;
    GLuint location_model;
    GLuint location_view;
    GLuint location_inv_view;

    GLuint location_num_lights;
    GLuint location_shininess;
    GLuint location_emission;

    GLuint location_mtl_ambient;
    GLuint location_mtl_diffuse;
    GLuint location_mtl_specular;
};
}  // namespace ore
