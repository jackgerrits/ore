#include "basic_shader.hpp"

#include <iostream>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace ore {
    basic_shader::basic_shader(): shader_program(BASIC_VERTEX_SHADER, BASIC_FRAGMENT_SHADER) {
        bind_uniform_locations();
    }

    void basic_shader::bind_uniform_locations() {
        glBindAttribLocation(shaderID, 0, "a_vertex");
    }
}
