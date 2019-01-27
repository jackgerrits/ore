#ifndef ENTITYSHADER_H
#define ENTITYSHADER_H

#define _USE_MATH_DEFINES

#include <ore/shaders/shader_program.hpp>
#include <ore/entity.hpp>
#include <ore/model.hpp>
#include <ore/components/light_component.hpp>
#include <ore/components/camera_component.hpp>

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>

#include "base_dir.h"

namespace ore {
    // TODO: Determine better way to reference shaders that isn't relative to current directory.
    const std::string ENTITY_VERTEX_SHADER = PROJECT_DIR "src/shaders/entity.vert";
    const std::string ENTITY_FRAGMENT_SHADER = PROJECT_DIR "src/shaders/entity.frag";

    class entity_shader : public shader_program {
    public:
        entity_shader();

        virtual void bindUniformLocations();

        void loadLights(std::vector<entity*> lights);
        void loadLight(entity* light, int i);
        void loadView(glm::mat4 view);
        void loadEntity(entity* entity);
        void loadModelPart(const model_part& component);
        void loadProjection(glm::mat4 proj);
    //     void loadDepth(glm::mat4 pv);
    //     void loadClipPlane(glm::vec4 clip);

    private:
        GLuint location_texMap;
        GLuint location_cubeMap;
        // GLuint location_shadowMap;
        // GLuint location_clip_plane;

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

        // GLuint location_depth_pv;
        // GLuint location_render_shadows;
    };
}

#endif //ENTITYSHADER_H
