#pragma once

#include <ore/components/component.h>

#include <glm/ext.hpp>
#include <glm/matrix.hpp>

namespace ore {
class position_3d_component : public base_component<position_3d_component> {
   public:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    // TODO initialize
    float xRot = 0.f;
    float yRot = 0.f;
    float zRot = 0.f;

    position_3d_component()
        : position(glm::vec3(0.0f, 0.0f, 0.0f)),
          scale(glm::vec3(1.0f, 1.0f, 1.0f)),
          rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {}

    virtual std::string get_type() const { return "position"; }
};

inline void move(position_3d_component& p3d, glm::vec3) {
    // TODO implement
}

inline glm::vec3 get_direction_vector(position_3d_component& p3d) {
    return glm::normalize(
        glm::vec3(glm::sin(p3d.yRot), glm::sin(p3d.xRot), glm::cos(p3d.yRot)));
}

inline void place_bottom_edge(position_3d_component& p3d, float surfaceY) {
    // TODO implement

    /*	if (model) {
            position.y = surfaceY - model->get_range_in_dim(1).first * scale.y;
        }*/
}

inline glm::mat4 calculate_rotation_matrix(position_3d_component& p3d) {
    glm::mat4 rotation(1.0f);

    rotation = glm::rotate(rotation, p3d.xRot, glm::vec3(0.0f, 1.0f, 0.0f));
    rotation = glm::rotate(rotation, p3d.yRot, glm::vec3(1.0f, 0.0f, 0.0f));
    rotation = glm::rotate(rotation, p3d.zRot, glm::vec3(0.0f, 0.0f, 1.0f));

    return rotation;
}

inline glm::mat4 calculate_model_matrix(position_3d_component& p3d) {
    glm::mat4 modelMatrix(1.0f);

    auto rotation_matrix = calculate_rotation_matrix(p3d);

    // scale, rotate and translate
    modelMatrix = glm::translate(modelMatrix, p3d.position);
    modelMatrix = modelMatrix * rotation_matrix;
    modelMatrix = glm::scale(modelMatrix, p3d.scale);

    return modelMatrix;
}

}  // namespace ore
