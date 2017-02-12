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
    class ModelPart {
    private:
        GLuint vaoID;
        int indexCount;
        Material material;

    public:
        GLuint textureID;
        ModelPart(GLuint, int, GLuint, Material);
        ModelPart(GLuint, int, GLuint);
        ModelPart();

        int getIndexCount() const;
        GLuint getVaoID() const;
        GLuint getTextureID() const;
        Material getMaterial() const;
    };

    // Represents a grouping of meshes/shapes/vaos/ModelParts to form a larger object.
    class Model {
    private:
        std::vector<ModelPart> parts;
        std::vector<float> maxRanges;   // Essentially forms a bounding box for the model. Format: [xMin, xMax, yMin, yMax, zMin, zMax]
    public:
        Model(std::vector<ModelPart>);
        Model();
        void addModelPart(ModelPart);
        const std::vector<ModelPart>& getModelParts();

        void addRange(std::vector<float> vertices);
        std::pair<float, float> getRangeInDim(int dim);
    };
}

#endif
