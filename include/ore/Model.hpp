#ifndef MODEL_H
#define MODEL_H

#define _USE_MATH_DEFINES

#include <ore/Material.hpp>

#include <vector>
#include <cfloat>
#include <utility>
#include <algorithm>
#include <iostream>

#include <GL/glew.h>

namespace ore {
    // Represents a single mesh/shape/vao
    class ModelComponent {
    private:
        GLuint vaoID;
        int indexCount;
        Material material;

    public:
        GLuint textureID;
        ModelComponent(GLuint, int, GLuint, Material);
        ModelComponent(GLuint, int, GLuint);
        ModelComponent();

        int getIndexCount() const;
        GLuint getVaoID() const;
        GLuint getTextureID() const;
        Material getMaterial() const;
    };

    // Represents a grouping of meshes/shapes/vaos/ModelComponents to form a larger object.
    class Model {
    private:
        std::vector<ModelComponent> components;
        std::vector<float> maxRanges;   // Essentially forms a bounding box for the model. Format: [xMin, xMax, yMin, yMax, zMin, zMax]
    public:
        Model(std::vector<ModelComponent>);
        Model();
        void addModelComponent(ModelComponent);
        std::vector<ModelComponent>* getModelComponents();

        void addRange(std::vector<float> vertices);
        std::pair<float, float> getRangeInDim(int dim);
    };
}

#endif
