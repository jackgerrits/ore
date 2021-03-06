#pragma once

#include <glad/glad.h>

#include <cstdio>
#include <glm/glm.hpp>
#include <sstream>
#include <string>

namespace ore {
std::string read_file_into_string(const char* filePath);
void compile_shader(const char* shaderPath, GLuint shaderID);
GLuint load_shaders(const char* vertex_file_path,
                    const char* fragment_file_path);

// Abstract shader program class, holds all uniforms.
class shader_program {
   public:
    shader_program(std::string, std::string);
    shader_program(int);

    virtual void enable();
    virtual void disable();

    GLuint get_shader_id() const;

    template <typename T>
    void load_light_uniform(std::string property, int index, const T& value);

    // Uniform loading helpers
    static void load_uniform_value(GLuint uniformLocation, int value);
    static void load_uniform_value(GLuint uniformLocation, unsigned int value);
    static void load_uniform_value(GLuint uniformLocation, float value);
    static void load_uniform_value(GLuint uniformLocation, glm::vec2 value);
    static void load_uniform_value(GLuint uniformLocation, glm::vec3 value);
    static void load_uniform_value(GLuint uniformLocation, glm::vec4 value);
    static void load_uniform_value(GLuint uniformLocation, glm::mat2 value);
    static void load_uniform_value(GLuint uniformLocation, glm::mat3 value);
    static void load_uniform_value(GLuint uniformLocation, glm::mat4 value);
    static void load_uniform_value(GLuint uniformLocation, float* value,
                                   int count);

   protected:
    GLuint shaderID;
};

// TODO: Should generalise this to take 'lights' as a paramter
template <typename T>
void shader_program::load_light_uniform(std::string property, int index,
                                        const T& value) {
    // Lights are passed as an array of structs. However these are essentially
    // bound and send individually. They have special uniform name syntax
    // though. ie uniform_name[i].property -> lights[0].position
    std::ostringstream ss;
    ss << "lights[" << index << "]." << property;
    std::string uniformName = ss.str();

    GLuint uniform_location =
        glGetUniformLocation(shaderID, uniformName.c_str());
    load_uniform_value(uniform_location, value);
}
}  // namespace ore
