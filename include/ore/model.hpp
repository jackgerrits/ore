#pragma once



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
        size_t indexCount;
        material material;

    public:
        GLuint textureID;
        model_part(GLuint, size_t, GLuint, ore::material);
        model_part(GLuint, size_t, GLuint);
        model_part();

        size_t get_index_count() const;
        GLuint get_vao_id() const;
        GLuint get_texture_id() const;
        ore::material get_material() const;
    };

    // Represents a grouping of meshes/shapes/vaos/ModelParts to form a larger object.
    class model {
    private:
        std::vector<model_part> parts;
        std::vector<float> maxRanges;   // Essentially forms a bounding box for the model. Format: [xMin, xMax, yMin, yMax, zMin, zMax]
    public:
        model(std::vector<model_part>);
        model();
        void add_model_part(model_part);
        const std::vector<model_part>& get_model_parts();

        void add_range(std::vector<float> vertices);
        std::pair<float, float> get_range_in_dim(int dim);
    };
}
