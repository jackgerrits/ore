#include <ore/shaders/shader_program.hpp>

#include <fstream>
#include <vector>
#include <iostream>

#include <glm/ext.hpp>

using namespace ore;

shader_program::shader_program(std::string vertexShader, std::string fragmentShader){
    this->shaderID = loadShaders(vertexShader.c_str(), fragmentShader.c_str());
}

shader_program::shader_program(int shaderID){
    this->shaderID = shaderID;
}

void shader_program::enable(){
    glUseProgram(shaderID);
}

void shader_program::disable(){
    glUseProgram(0);
}

GLuint shader_program::getShaderID() {
    return shaderID;
}

void shader_program::loadUniformValue(GLuint uniformLocation, int value){
    glUniform1i(uniformLocation, value);
}

void shader_program::loadUniformValue(GLuint uniformLocation, unsigned int value) {
    glUniform1i(uniformLocation, value);
}

void shader_program::loadUniformValue(GLuint uniformLocation, float value){
    glUniform1f(uniformLocation, value);
}

void shader_program::loadUniformValue(GLuint uniformLocation, glm::vec2 value){
    glUniform2fv(uniformLocation, 1, &value.x);
}

void shader_program::loadUniformValue(GLuint uniformLocation, glm::vec3 value){
    glUniform3fv(uniformLocation, 1, &value.x);
}

void shader_program::loadUniformValue(GLuint uniformLocation, glm::vec4 value){
    glUniform4fv(uniformLocation, 1, &value.x);
}

void shader_program::loadUniformValue(GLuint uniformLocation, glm::mat2 value){
    glUniformMatrix2fv(uniformLocation, 1, false, glm::value_ptr(value));
}

void shader_program::loadUniformValue(GLuint uniformLocation, glm::mat3 value){
    glUniformMatrix3fv(uniformLocation, 1, false, glm::value_ptr(value));
}

void shader_program::loadUniformValue(GLuint uniformLocation, glm::mat4 value){
    glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(value));
}

void shader_program::loadUniformValue(GLuint uniformLocation, float* value, int count) {
    switch(count){
        case 1:
            glUniform1f(uniformLocation, *value);
            break;
        case 2:
            glUniform2fv(uniformLocation, 1, value);
            break;
        case 3:
            glUniform3fv(uniformLocation, 1, value);
            break;
        case 4:
            glUniform4fv(uniformLocation, 1, value);
            break;
        default:
            throw std::runtime_error("Cant load uniform with " + std::to_string(count) + " dimensions.");
    }
}

std::string ore::readFileIntoString(const char* filePath) {
    std::string fileContents;
    std::ifstream fileStream(filePath, std::ios::in);

    // If the file can't be opened, return an empty optional.
    if(!fileStream.is_open()) {
        throw std::invalid_argument("Cannot open " + std::string(filePath) + ". Are you in the right directory?");
    }

    fileStream.seekg(0, std::ios::end);
    fileContents.reserve(fileStream.tellg());
    fileStream.seekg(0, std::ios::beg);

    fileContents.assign((std::istreambuf_iterator<char>(fileStream)),
        std::istreambuf_iterator<char>());

    return fileContents;
}

// Compile the shader file at the at the path for the shader id. Throws on failure;
void ore::compileShader(const char* shaderPath, const GLuint shaderID) {
    // Consider using std::tie here for readability.
    auto fileContents = readFileIntoString(shaderPath);

    // Compile Shader
    auto SourcePointer = fileContents.c_str();
    glShaderSource(shaderID, 1, &SourcePointer , NULL);
    glCompileShader(shaderID);

    // Check Shader
    GLint result = GL_FALSE;
    int infoLogLength;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 1) {
        std::vector<char> error_message_buffer(infoLogLength);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, error_message_buffer.data());
        throw std::invalid_argument(std::string(begin(error_message_buffer), end(error_message_buffer)));
    }
}

GLuint ore::loadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    // Create the shaders.
    GLuint vertexshaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentshaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile both shaders. Will throw if there are compile errors.
    compileShader(vertex_file_path, vertexshaderID);
    compileShader(fragment_file_path, fragmentshaderID);

    // Link the program.
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexshaderID);
    glAttachShader(programID, fragmentshaderID);
    glLinkProgram(programID);

    // Check the program.
    GLint result = GL_FALSE;
    int infoLogLength;

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> error_message_buffer(infoLogLength);
        glGetProgramInfoLog(programID, infoLogLength, NULL, error_message_buffer.data());
        throw std::invalid_argument(std::string(begin(error_message_buffer), end(error_message_buffer)));
    }

    glDeleteShader(vertexshaderID);
    glDeleteShader(fragmentshaderID);

    return programID;
}
