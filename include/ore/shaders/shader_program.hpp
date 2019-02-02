#pragma once

#define _USE_MATH_DEFINES

#include <cstdio>
#include <string>
#include <sstream>

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace ore {
	std::string readFileIntoString(const char* filePath);
	void compileShader(const char* shaderPath, const GLuint shaderID);
	GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);

	// Abstract shader program class, holds all uniforms.
	class shader_program {
	public:
		shader_program(std::string, std::string);
		shader_program(int);

		virtual void bindUniformLocations() = 0;
		virtual void enable();
		virtual void disable();

		GLuint getShaderID();

		template <typename T>
		void loadLightUniform(std::string property, int index, const T& value);

		// Uniform loading helpers
		static void loadUniformValue(GLuint uniformLocation, int value);
		static void loadUniformValue(GLuint uniformLocation, unsigned int value);
		static void loadUniformValue(GLuint uniformLocation, float value);
		static void loadUniformValue(GLuint uniformLocation, glm::vec2 value);
		static void loadUniformValue(GLuint uniformLocation, glm::vec3 value);
		static void loadUniformValue(GLuint uniformLocation, glm::vec4 value);
		static void loadUniformValue(GLuint uniformLocation, glm::mat2 value);
		static void loadUniformValue(GLuint uniformLocation, glm::mat3 value);
		static void loadUniformValue(GLuint uniformLocation, glm::mat4 value);
		static void loadUniformValue(GLuint uniformLocation, float* value, int count);

	protected:
		GLuint shaderID;
	};

	// TODO: Should generalise this to take 'lights' as a paramter
	template <typename T>
	void shader_program::loadLightUniform(std::string property, int index, const T& value) {
		// Lights are passed as an array of structs. However these are essentially bound and send individually.
		// They have special uniform name syntax though. ie uniform_name[i].property -> lights[0].position
		std::ostringstream ss;
		ss << "lights[" << index << "]." << property;
		std::string uniformName = ss.str();

		GLuint uniform_location = glGetUniformLocation(shaderID, uniformName.c_str());
		loadUniformValue(uniform_location, value);
	}
}