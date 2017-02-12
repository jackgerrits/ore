#include <ore/shaders/EntityShader.hpp>

namespace ore {
    EntityShader::EntityShader(): ShaderProgram(ENTITY_VERTEX_SHADER, ENTITY_FRAGMENT_SHADER) {
        bindUniformLocations();
    }

    void EntityShader::bindUniformLocations(){
        // Setup named attributes
        glBindAttribLocation(shaderID, 0, "a_vertex");
        glBindAttribLocation(shaderID, 1, "a_normal");
        glBindAttribLocation(shaderID, 2, "a_tex_coord");

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

    void EntityShader::loadLights(std::vector<Entity*> lights){
        loadUniformValue(location_num_lights, int(lights.size()));
        for(size_t i = 0; i < lights.size(); i++){
            loadLight(lights[i], i);
        }
    }

    void EntityShader::loadLight(Entity* light, int i){
        LightComponent* lightComponent = light->getComponent<LightComponent>();

        loadLightUniform("position", i, lightComponent->position);
        loadLightUniform("specular", i, lightComponent->specular);
        loadLightUniform("diffuse", i, lightComponent->diffuse);
        loadLightUniform("ambient", i, lightComponent->ambient);
        loadLightUniform("radius", i, lightComponent->radius);
        loadLightUniform("coneAngle", i, lightComponent->coneAngle);
        loadLightUniform("coneDirection", i, lightComponent->coneDirection);
    }

    void EntityShader::loadView(glm::mat4 view){
        loadUniformValue(location_view, view);
        loadUniformValue(location_inv_view, glm::inverse(view));
    }

    void EntityShader::loadEntity(Entity* entity){
        // loadUniformValue(location_texMap, 0);
        // loadUniformValue(location_cubeMap, 1);
        glm::mat4 model = entity->getModelMatrix();

        loadUniformValue(location_model, model);
    }

    void EntityShader::loadModelPart(const ModelPart& component){
        loadUniformValue(location_mtl_ambient, component.getMaterial().ambient.data(), 3);
        loadUniformValue(location_mtl_diffuse, component.getMaterial().diffuse.data(), 3);
        loadUniformValue(location_mtl_specular, component.getMaterial().specular.data(), 3);
        loadUniformValue(location_emission, component.getMaterial().emission.data(), 3);
        loadUniformValue(location_shininess, component.getMaterial().shininess);
    }

    void EntityShader::loadProjection(glm::mat4 proj){
        loadUniformValue(location_projection, proj);
        // loadUniformValue(location_render_shadows, 0);
    }

    // void EntityShader::loadClipPlane(glm::vec4 clip){
    //     loadUniformValue(location_clip_plane, clip);
    // }

    // void EntityShader::loadDepth(glm::mat4 pv){
    //     loadUniformValue(location_shadowMap, 2);
    //     loadUniformValue(location_depth_pv, pv);
    //     loadUniformValue(location_render_shadows, 1);
    // }
}
