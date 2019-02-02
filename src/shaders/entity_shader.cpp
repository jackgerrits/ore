#include <ore/shaders/entity_shader.hpp>

#include <ore/components/position_3d_component.hpp>

#include <iostream>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace ore {
    entity_shader::entity_shader(): shader_program(ENTITY_VERTEX_SHADER, ENTITY_FRAGMENT_SHADER) {
        bindUniformLocations();
    }

    void entity_shader::bindUniformLocations(){
        // Setup named attributes
 /*       glBindAttribLocation(shaderID, 0, "a_vertex");
        glBindAttribLocation(shaderID, 1, "a_normal");
        glBindAttribLocation(shaderID, 2, "a_tex_coord");*/

        location_texMap = glGetUniformLocation(shaderID, "texMap");
        location_cubeMap = glGetUniformLocation(shaderID, "cubeMap");
        // location_shadowMap = glGetUniformLocation(shaderID, "shadowMap");
        // location_clip_plane = glGetUniformLocation(shaderID, "clip_plane");

        location_projection = glGetUniformLocation(shaderID, "projection");
        location_model = glGetUniformLocation(shaderID, "model");
        location_view = glGetUniformLocation(shaderID, "view");
        location_inv_view = glGetUniformLocation(shaderID, "inv_view");

        location_shininess = glGetUniformLocation(shaderID, "shininess");
        location_emission = glGetUniformLocation(shaderID, "emission");
        location_num_lights = glGetUniformLocation(shaderID, "num_lights");
        location_mtl_ambient = glGetUniformLocation(shaderID, "mtl_ambient");
        location_mtl_diffuse = glGetUniformLocation(shaderID, "mtl_diffuse");
        location_mtl_specular = glGetUniformLocation(shaderID, "mtl_specular");

        // location_depth_pv = glGetUniformLocation(shaderID, "depth_pv");
        // location_render_shadows = glGetUniformLocation(shaderID, "render_shadows");
    }

    void entity_shader::loadLights(std::vector<entity*> lights){
        loadUniformValue(location_num_lights, int(lights.size()));
        for(size_t i = 0; i < lights.size(); i++){
            loadLight(lights[i], i);
        }
    }

    void entity_shader::loadLight(entity* light, int i){
        light_component* lightComponent = light->getComponent<light_component>();

        loadLightUniform("position", i, lightComponent->position);
        loadLightUniform("specular", i, lightComponent->specular);
        loadLightUniform("diffuse", i, lightComponent->diffuse);
        loadLightUniform("ambient", i, lightComponent->ambient);
        loadLightUniform("radius", i, lightComponent->radius);
        loadLightUniform("coneAngle", i, lightComponent->coneAngle);
        loadLightUniform("coneDirection", i, lightComponent->coneDirection);
    }

    void entity_shader::loadView(glm::mat4 view){
        loadUniformValue(location_view, view);
        loadUniformValue(location_inv_view, glm::inverse(view));
    }

    void entity_shader::loadEntity(entity* entity){
        // loadUniformValue(location_texMap, 0);
        // loadUniformValue(location_cubeMap, 1);
		glm::mat4 model = ore::calculateModelMatrix(*entity->getComponent<position_3d_component>());

        loadUniformValue(location_model, model);
    }

    void entity_shader::loadModelPart(const model_part& component){
        loadUniformValue(location_mtl_ambient, component.getMaterial().ambient.data(), 3);
        loadUniformValue(location_mtl_diffuse, component.getMaterial().diffuse.data(), 3);
        loadUniformValue(location_mtl_specular, component.getMaterial().specular.data(), 3);
        loadUniformValue(location_emission, component.getMaterial().emission.data(), 3);
        loadUniformValue(location_shininess, component.getMaterial().shininess);
    }

    void entity_shader::loadProjection(glm::mat4 proj){
        loadUniformValue(location_projection, proj);
        // loadUniformValue(location_render_shadows, 0);
    }

    // void entity_shader::loadClipPlane(glm::vec4 clip){
    //     loadUniformValue(location_clip_plane, clip);
    // }

    // void entity_shader::loadDepth(glm::mat4 pv){
    //     loadUniformValue(location_shadowMap, 2);
    //     loadUniformValue(location_depth_pv, pv);
    //     loadUniformValue(location_render_shadows, 1);
    // }
}
