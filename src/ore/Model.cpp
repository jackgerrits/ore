#include <ore/Model.hpp>

namespace ore {
    ModelPart::ModelPart(GLuint vaoID, int indexCount, GLuint textureID, Material material) {
        this->vaoID = vaoID;
        this->indexCount = indexCount;
        this->textureID = textureID;
        this->material = material;
    }

    ModelPart::ModelPart(GLuint vaoID, int indexCount, GLuint textureID) {
        this->vaoID = vaoID;
        this->indexCount = indexCount;
        this->textureID = textureID;
    }

    ModelPart::ModelPart() {
        this->vaoID = -1;
        this->indexCount = -1;
        this->textureID = -1;
    }

    int ModelPart::getIndexCount() const {
        return indexCount;
    }

    GLuint ModelPart::getVaoID() const {
        return vaoID;
    }

    GLuint ModelPart::getTextureID() const {
        return textureID;
    }

    Material ModelPart::getMaterial() const {
        return material;
    }

    Model::Model(std::vector<ModelPart> parts) {
        this->parts = parts;

        for(int i = 0; i < 3; ++i) {
            maxRanges.push_back(FLT_MAX);
            maxRanges.push_back(-FLT_MAX);
        }
    }

    // Adds the vertices into the range stored for this model.
    void Model::addRange(std::vector<float> vertices) {
        for(int dim = 0; dim < 3; ++dim) {
            for(size_t j = dim; j < vertices.size(); j += 3) {
                maxRanges[2 * dim] = std::min(vertices[j], maxRanges[2 * dim]);
                maxRanges[2 * dim + 1] = std::max(vertices[j], maxRanges[2 * dim + 1]);
            }
        }
    }

    std::pair<float, float> Model::getRangeInDim(int dim) {
        return std::pair<float, float>( maxRanges[2 * dim],  maxRanges[2 * dim + 1]);
    }

    Model::Model() {
        for(int i = 0; i < 3; ++i) {
            maxRanges.push_back(FLT_MAX);
            maxRanges.push_back(-FLT_MAX);
        }
    }

    void Model::addModelPart(ModelPart part) {
        parts.push_back(part);
    }

    const std::vector<ModelPart>& Model::getModelParts() {
        return parts;
    }
}
