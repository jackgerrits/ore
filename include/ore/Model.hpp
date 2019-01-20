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
    class model_part {
    private:
        GLuint vaoID;
        int indexCount;
        material material;

    public:
        GLuint textureID;
        model_part(GLuint, int, GLuint, ore::material);
        model_part(GLuint, int, GLuint);
        model_part();

        int getIndexCount() const;
        GLuint getVaoID() const;
        GLuint getTextureID() const;
        ore::material getMaterial() const;
    };

    // Represents a grouping of meshes/shapes/vaos/ModelParts to form a larger object.
    class model {
    private:
        std::vector<model_part> parts;
        std::vector<float> maxRanges;   // Essentially forms a bounding box for the model. Format: [xMin, xMax, yMin, yMax, zMin, zMax]
    public:
        model(std::vector<model_part>);
        model();
        void addModelPart(model_part);
        const std::vector<model_part>& getModelParts();

        void addRange(std::vector<float> vertices);
        std::pair<float, float> getRangeInDim(int dim);
    };
}

#endif
