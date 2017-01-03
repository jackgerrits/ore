#include <ore/shaders/ShaderProgram.h>

ShaderProgram::ShaderProgram(std::string vertexShader, std::string fragmentShader){
    this->shaderID = loadShaders(vertexShader.c_str(), fragmentShader.c_str());
}

ShaderProgram::ShaderProgram(int shaderID){
    this->shaderID = shaderID;
}

void ShaderProgram::enable(){
    glUseProgram(shaderID);
}

void ShaderProgram::disable(){
    glUseProgram(0);
}

GLuint ShaderProgram::getShaderID() {
    return shaderID;
}

void ShaderProgram::loadUniformValue(GLuint uniformLocation, int value){
    glUniform1i(uniformLocation, value);
}

void ShaderProgram::loadUniformValue(GLuint uniformLocation, float value){
    glUniform1f(uniformLocation, value);
}

void ShaderProgram::loadUniformValue(GLuint uniformLocation, glm::vec2 value){
    glUniform2fv(uniformLocation, 1, &value.x);
}

void ShaderProgram::loadUniformValue(GLuint uniformLocation, glm::vec3 value){
    glUniform3fv(uniformLocation, 1, &value.x);
}

void ShaderProgram::loadUniformValue(GLuint uniformLocation, glm::vec4 value){
    glUniform4fv(uniformLocation, 1, &value.x);
}

void ShaderProgram::loadUniformValue(GLuint uniformLocation, glm::mat2 value){
    glUniformMatrix2fv(uniformLocation, 1, false, glm::value_ptr(value));
}

void ShaderProgram::loadUniformValue(GLuint uniformLocation, glm::mat3 value){
    glUniformMatrix3fv(uniformLocation, 1, false, glm::value_ptr(value));
}

void ShaderProgram::loadUniformValue(GLuint uniformLocation, glm::mat4 value){
    glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(value));
}

void ShaderProgram::loadUniformValue(GLuint uniformLocation, float* value, int count){
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
            std::cerr << "Cant load uniform with " << count << " dimensions." << std::endl;
            break;
    }
}

// If the file cannot be opened the second value in the pair will be false.
// The pair represents (file_contents, success)
std::pair<std::string, bool> ShaderProgram::readFile(const char* filePath) {
    std::string fileContents;
    std::ifstream fileStream(filePath, std::ios::in);

    // If the file can't be opened, return an empty optional.
    if(!fileStream.is_open()) {
        return std::make_pair("", false);
    }

    fileStream.seekg(0, std::ios::end);
    fileContents.reserve(fileStream.tellg());
    fileStream.seekg(0, std::ios::beg);

    fileContents.assign((std::istreambuf_iterator<char>(fileStream)),
        std::istreambuf_iterator<char>());

    return std::make_pair(fileContents, true);
}

// Compile the shader file at the at the path for the shader id. Returns true for success.
bool ShaderProgram::compileShader(const char *shaderPath, const GLuint shaderID) {
    // Consider using std::tie here for readability.
    auto contentsOptional = readFile(shaderPath);

    // If it the file read was not successful.
    if(!contentsOptional.second) {
        std::cerr << "Cannot open " << shaderPath << ". Are you in the right directory?" << std::endl;
        return 0;
    }

    // Compile Shader
    char const *SourcePointer = contentsOptional.first.c_str();
    glShaderSource(shaderID, 1, &SourcePointer , NULL);
    glCompileShader(shaderID);

    // Check Shader
    GLint result = GL_FALSE;
    int infoLogLength;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 1) {
        char* ShaderErrorMessage = new char[infoLogLength+1];
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &ShaderErrorMessage[0]);
        std::cerr << &ShaderErrorMessage[0] << std::endl;

        delete[] ShaderErrorMessage;
        return false;
    }

    return true;
}

GLuint ShaderProgram::loadShaders(const char * vertex_file_path, const char * fragment_file_path ) {
    // Create the shaders.
    GLuint vertexshaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentshaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile both shaders. Exit if compile errors.
    if (!compileShader(vertex_file_path, vertexshaderID)
         || !compileShader(fragment_file_path, fragmentshaderID)) {
        return 0;
    }

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
        char* programErrorMessage = new char[infoLogLength+1];
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
        std::cerr << &programErrorMessage[0] << std::endl;

        delete[] programErrorMessage;
    }

    glDeleteShader(vertexshaderID);
    glDeleteShader(fragmentshaderID);

    return programID;
}
