#include "basic_shader.h"

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>

namespace ore {
basic_shader::basic_shader()
    : shader_program(BASIC_VERTEX_SHADER, BASIC_FRAGMENT_SHADER) {

    glBindAttribLocation(shaderID, 0, "a_vertex");
}
}  // namespace ore
