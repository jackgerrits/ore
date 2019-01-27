#include "basic_shader.hpp"

#include <iostream>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace ore {
    basic_shader::basic_shader(): shader_program(BASIC_VERTEX_SHADER, BASIC_FRAGMENT_SHADER) {
        bindUniformLocations();
    }

    void basic_shader::bindUniformLocations() {
        glBindAttribLocation(shaderID, 0, "a_vertex");
    }
}
