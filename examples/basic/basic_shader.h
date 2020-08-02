#pragma once

#include <glad/glad.h>
#include <ore/shaders/shader_program.h>

#include <cstdio>
#include <fstream>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "resource_path.hpp"

namespace ore {
const std::string BASIC_VERTEX_SHADER = BASIC_RES_DIR "basic.vert";
const std::string BASIC_FRAGMENT_SHADER = BASIC_RES_DIR "basic.frag";

class basic_shader : public shader_program {
   public:
    basic_shader();
};
}  // namespace ore
