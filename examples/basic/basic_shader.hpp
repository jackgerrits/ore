#pragma once



#include <ore/shaders/shader_program.hpp>

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>

#include "resource_path.hpp"

namespace ore {
    const std::string BASIC_VERTEX_SHADER = BASIC_RES_DIR "basic.vert";
    const std::string BASIC_FRAGMENT_SHADER = BASIC_RES_DIR "basic.frag";

    class basic_shader : public shader_program {
    public:
        basic_shader();
        virtual void bindUniformLocations() override;
    };
}
