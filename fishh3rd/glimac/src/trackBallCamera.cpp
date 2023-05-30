#include "glimac/trackBallCamera.hpp"

namespace glimac {

void Camera::moveFront(float delta) {
    this->m_distance += delta;
}

void Camera::rotateLeft(float degrees) {
    this->m_fAngleY += degrees;
}

void Camera::rotateUp(float degrees) {
    this->m_fAngleX += degrees;
}

glm::mat4 Camera::getViewMatrix() const {
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -m_distance));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    return viewMatrix;
}

}