#pragma once



#include <ore/model.hpp>
#include <ore/Image.hpp>
#include <ore/lib/stb_image.h>
#include <ore/lib/tiny_obj_loader.h>

#include <sys/stat.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <glm/glm.hpp>

namespace ore {
    class loader {
    private:
        loader();

        // Stores the file/id mapping for each loaded texture to use for caching.
        std::map<std::string, GLuint> loadedTextures;
        GLuint load_texture_data(GLubyte* data, int x, int y, int n, GLenum textureUnit);
        GLuint setup_buffer(unsigned int buffer, std::vector<float> values, int attributeIndex, int dataDimension);
        GLuint setup_indices_buffer(unsigned int buffer, std::vector<unsigned int> values);
    public:
        static loader& get();

        std::vector<float> generate_normals(std::vector<float> vertices, std::vector<unsigned int> indices);

        bool file_exists(const std::string& name);
        std::shared_ptr<model> load_model(std::string filepath);
        std::shared_ptr<model> load_model(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials, std::string materialpath);
        model_part load_model_part(tinyobj::shape_t, std::vector<tinyobj::material_t> materials, std::string materialpath);
        model_part load_model_part(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords);
        model_part load_model_part(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords, std::vector<float> normals);
        model_part load_model_part(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords, std::string texturepath);
        model_part load_model_part(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords, std::vector<float> normals, std::string texturepath);

        GLuint load_vao(std::vector<float> vertices, std::vector<unsigned int> indices);
        GLuint load_vao(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords);
        GLuint load_vao(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords, std::vector<float> normals);
        GLuint load_vao(tinyobj::shape_t);

        std::unique_ptr<image> load_image(std::string filepath);
        GLuint load_cubemap_texture(std::vector<std::string> filenames);
        GLuint load_texture(std::string filepath);
        GLuint load_default_texture();
    };
}
