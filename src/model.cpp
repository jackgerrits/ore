#include <ore/model.hpp>
#include <ore/material.hpp>

namespace ore {
    model_part::model_part(GLuint vaoID, size_t indexCount, GLuint textureID, ore::material material) {
        this->vaoID = vaoID;
        this->indexCount = indexCount;
        this->textureID = textureID;
        this->material = material;
    }

    model_part::model_part(GLuint vaoID, size_t indexCount, GLuint textureID) {
        this->vaoID = vaoID;
        this->indexCount = indexCount;
        this->textureID = textureID;
    }

    model_part::model_part() {
        this->vaoID = -1;
        this->indexCount = 0;
        this->textureID = -1;
    }

    size_t model_part::getIndexCount() const {
        return indexCount;
    }

    GLuint model_part::getVaoID() const {
        return vaoID;
    }

    GLuint model_part::getTextureID() const {
        return textureID;
    }

    material model_part::getMaterial() const {
        return material;
    }

    model::model(std::vector<model_part> parts) {
        this->parts = parts;

        for(int i = 0; i < 3; ++i) {
            maxRanges.push_back(FLT_MAX);
            maxRanges.push_back(-FLT_MAX);
        }
    }

    // Adds the vertices into the range stored for this model.
    void model::addRange(std::vector<float> vertices) {
        for(int dim = 0; dim < 3; ++dim) {
            for(size_t j = dim; j < vertices.size(); j += 3) {
                maxRanges[2 * dim] = std::min(vertices[j], maxRanges[2 * dim]);
                maxRanges[2 * dim + 1] = std::max(vertices[j], maxRanges[2 * dim + 1]);
            }
        }
    }

    std::pair<float, float> model::getRangeInDim(int dim) {
        return std::pair<float, float>( maxRanges[2 * dim],  maxRanges[2 * dim + 1]);
    }

    model::model() {
        for(int i = 0; i < 3; ++i) {
            maxRanges.push_back(FLT_MAX);
            maxRanges.push_back(-FLT_MAX);
        }
    }

    void model::addModelPart(model_part part) {
        parts.push_back(part);
    }

    const std::vector<model_part>& model::getModelParts() {
        return parts;
    }
}
