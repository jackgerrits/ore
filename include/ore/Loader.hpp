#pragma once

#define _USE_MATH_DEFINES

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
        GLuint loadTextureData(GLubyte *data, int x, int y, int n, GLenum textureUnit);
        GLuint setupBuffer(unsigned int buffer, std::vector<float> values, int attributeIndex, int dataDimension);
        GLuint setupIndicesBuffer(unsigned int buffer, std::vector<unsigned int> values);
    public:
        static loader& getLoader();

        std::vector<float> generateNormals(std::vector<float> vertices, std::vector<unsigned int> indices);

        bool fileExists(const std::string& name);
        std::shared_ptr<model> loadModel(std::string filepath);
        std::shared_ptr<model> loadModel(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials, std::string materialpath);
        model_part loadModelPart(tinyobj::shape_t, std::vector<tinyobj::material_t> materials, std::string materialpath);
        model_part loadModelPart(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords);
        model_part loadModelPart(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords, std::vector<float> normals);
        model_part loadModelPart(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords, std::string texturepath);
        model_part loadModelPart(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords, std::vector<float> normals, std::string texturepath);

        GLuint loadVAO(std::vector<float> vertices, std::vector<unsigned int> indices);
        GLuint loadVAO(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords);
        GLuint loadVAO(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> texCoords, std::vector<float> normals);
        GLuint loadVAO(tinyobj::shape_t);

        std::unique_ptr<image> loadImage(std::string filepath);
        GLuint loadCubemapTexture(std::vector<std::string> filenames);
        GLuint loadTexture(std::string filepath);
        GLuint loadDefaultTexture();
    };
}
