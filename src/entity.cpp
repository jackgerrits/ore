#include <ore/entity.hpp>
#include <ore/model.hpp>

using namespace std;

namespace ore {

    // Constructor accepts a model defining vertex, colour and index data for this entity.
    entity::entity(shared_ptr<ore::model> model) {
        this->model = model;

        position = glm::vec3(0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
        xRot = 0.0f;
        yRot = 0.0f;
        zRot = 0.0f;
    }

    entity::entity() {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
        xRot = 0.0f;
        yRot = 0.0f;
        zRot = 0.0f;
    }

    std::vector<Component*> entity::getComponents() {
        std::vector<Component*> results;
        for(auto const& kv : components) {
            results.push_back(kv.second);
        }
        return results;
    }

    bool entity::update() {
        return false;
    }

    shared_ptr<model> entity::getModel() const {
        return model;
    }

    glm::mat4 entity::getModelMatrix() {
        glm::mat4 rotation = calculateRotationMatrix(xRot, yRot, zRot);
        return calculateModelMatrix(position, rotation, scale);
    }

    // Getters and setters for entity state values.
    glm::vec3 entity::getPosition() const {
        return position;
    }

    glm::vec3 entity::getScale() const {
        return scale;
    }

    float entity::getRotationX() const {
        return xRot;
    }

    float entity::getRotationY() const {
        return yRot;
    }

    float entity::getRotationZ() const {
        return zRot;
    }

    glm::vec3 entity::getDirectionVector() {
        return glm::normalize(glm::vec3(glm::sin(yRot), glm::sin(xRot), glm::cos(yRot)));
    }

    void entity::setPosition(glm::vec3 position) {
        this->position = position;
    }

    void entity::placeBottomEdge(float surfaceY) {
        if(model) {
            position.y = surfaceY - model->getRangeInDim(1).first * scale.y;
        }
    }

    void entity::setScale(glm::vec3 scale) {
        this->scale = scale;
    }

    void entity::setRotationX(float rot) {
        xRot = rot;
    }

    void entity::setRotationY(float rot) {
        yRot = rot;
    }

    void entity::setRotationZ(float rot) {
        zRot = rot;
    }
    // Set the value of rotation or position relatively (Takes into account current value)
    void entity::rotateX(float rot) {
        xRot += rot;
    }

    void entity::rotateY(float rot) {
        yRot += rot;
    }

    void entity::rotateZ(float rot) {
        zRot += rot;
    }

    void entity::move(glm::vec3 movement) {
        position = position + movement;
    }

    glm::mat4 entity::calculateModelMatrix(glm::vec3 position, glm::mat4 rotationMat, glm::vec3 scale) {
        glm::mat4 modelMatrix(1.0f);

        // scale, rotate and translate
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = modelMatrix * rotationMat;
        modelMatrix = glm::scale(modelMatrix, scale);

        return modelMatrix;
    }

    glm::mat4 entity::calculateRotationMatrix(float xRot, float yRot, float zRot) {
        glm::mat4 rotation(1.0f);

        rotation = glm::rotate(rotation, yRot, glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(rotation, xRot, glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, zRot, glm::vec3(0.0f, 0.0f, 1.0f));

        return rotation;
    }
}
