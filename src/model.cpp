#include <ore/model.hpp>
#include <ore/material.hpp>

namespace ore {
    model_part::model_part(GLuint vaoID, size_t indexCount, GLuint textureID, ore::material material) {
        this->vaoID = vaoID;
        this->indexCount = indexCount;
        this->textureID = textureID;
        this->m_material = material;
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

    size_t model_part::get_index_count() const {
        return indexCount;
    }

    GLuint model_part::get_vao_id() const {
        return vaoID;
    }

    GLuint model_part::get_texture_id() const {
        return textureID;
    }

    material model_part::get_material() const {
        return m_material;
    }

    model::model(std::vector<model_part> parts) {
        this->parts = parts;

        for(int i = 0; i < 3; ++i) {
            maxRanges.push_back(FLT_MAX);
            maxRanges.push_back(-FLT_MAX);
        }
    }

    // Adds the vertices into the range stored for this model.
    void model::add_range(std::vector<float> vertices) {
        for(int dim = 0; dim < 3; ++dim) {
            for(size_t j = dim; j < vertices.size(); j += 3) {
                maxRanges[2 * dim] = std::min(vertices[j], maxRanges[2 * dim]);
                maxRanges[2 * dim + 1] = std::max(vertices[j], maxRanges[2 * dim + 1]);
            }
        }
    }

    std::pair<float, float> model::get_range_in_dim(int dim) {
        return std::pair<float, float>( maxRanges[2 * dim],  maxRanges[2 * dim + 1]);
    }

    model::model() {
        for(int i = 0; i < 3; ++i) {
            maxRanges.push_back(FLT_MAX);
            maxRanges.push_back(-FLT_MAX);
        }
    }

    void model::add_model_part(model_part part) {
        parts.push_back(part);
    }

    const std::vector<model_part>& model::get_model_parts() {
        return parts;
    }
}
