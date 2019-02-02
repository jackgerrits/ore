#include <ore/shaders/entity_shader.hpp>

#include <ore/components/position_3d_component.hpp>
#include <ore/components/light_component.hpp>
#include <ore/components/camera_component.hpp>

#include <iostream>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace ore {
    entity_shader::entity_shader(): shader_program(ENTITY_VERTEX_SHADER, ENTITY_FRAGMENT_SHADER) {
        bind_uniform_locations();
    }

    void entity_shader::bind_uniform_locations(){

        location_texMap = glGetUniformLocation(shaderID, "texMap");

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
    }

    void entity_shader::load_lights(std::vector<entity*> lights){
        load_uniform_value(location_num_lights, int(lights.size()));
        for(size_t i = 0; i < lights.size(); i++){
            load_light(lights[i], i);
        }
    }

    void entity_shader::load_light(entity* light, size_t i){
        light_component* lightComponent = light->get_component<light_component>();

        load_light_uniform("position", i, lightComponent->position);
        load_light_uniform("specular", i, lightComponent->specular);
        load_light_uniform("diffuse", i, lightComponent->diffuse);
        load_light_uniform("ambient", i, lightComponent->ambient);
        load_light_uniform("radius", i, lightComponent->radius);
        load_light_uniform("coneAngle", i, lightComponent->coneAngle);
        load_light_uniform("coneDirection", i, lightComponent->coneDirection);
    }

    void entity_shader::load_view(glm::mat4 view){
        load_uniform_value(location_view, view);
        load_uniform_value(location_inv_view, glm::inverse(view));
    }

    void entity_shader::load_entity(entity* entity){
        load_uniform_value(location_texMap, 0);
        glm::mat4 model = ore::calculate_model_matrix(*entity->get_component<position_3d_component>());
        load_uniform_value(location_model, model);
    }

    void entity_shader::load_model_part(const model_part& component){
        load_uniform_value(location_texMap, component.get_texture_id());
        load_uniform_value(location_mtl_ambient, component.get_material().ambient.data(), 3);
        load_uniform_value(location_mtl_diffuse, component.get_material().diffuse.data(), 3);
        load_uniform_value(location_mtl_specular, component.get_material().specular.data(), 3);
        load_uniform_value(location_emission, component.get_material().emission.data(), 3);
        load_uniform_value(location_shininess, component.get_material().shininess);
    }

    void entity_shader::load_projection(glm::mat4 proj){
        load_uniform_value(location_projection, proj);
    }
}
