#include "glimac/fish.hpp"
#include <iostream>

namespace glimac {

double getAngle(double a, double b) {   
    return b > 0 ? std::acos(a) : -std::acos(a);
}

void Fish::move(const SDLWindowManager &wm) { 
    this->position(this->position()+(this->angle()*glm::vec3(this->speed())));
}

void Fish::turn(int axis, int dir, double str, double TURN_FACTOR) {

    glm::vec3 newAngle;

    if (axis == 0) { // 0, 1, 1 | YZ
        double angle = getAngle(this->angle()[1], this->angle()[2]);
        angle += TURN_FACTOR*dir*str;
        newAngle = glm::vec3(this->angle()[0], std::cos(angle), std::sin(angle));
    } else if (axis == 1) { // 1, 1, 0 | XY
        double angle = getAngle(this->angle()[0], this->angle()[1]);
        angle += TURN_FACTOR*dir*str;
        newAngle = glm::vec3(std::cos(angle), std::sin(angle), this->angle()[2]);
    } else if (axis == 2) { // 1, 0, 1 | XZ
        double angle = getAngle(this->angle()[0], this->angle()[2]);
        angle += TURN_FACTOR*dir*str;
        newAngle = glm::vec3(std::cos(angle), this->angle()[1], std::sin(angle));
    } else {
        newAngle = glm::vec3(this->angle()[0], this->angle()[1], this->angle()[2]);
    }

    this->m_angle = newAngle;
}

glm::mat4 Fish::getRotationMatrix() const {
    glm::vec3 originalVec = {0, 0, -1};
    glm::vec3 targetVec   = this->m_angle;

    glm::vec3 axis  = glm::cross(originalVec, targetVec);
    float     angle = glm::acos(glm::dot(originalVec, targetVec) / (glm::length(originalVec) * glm::length(targetVec)));

    glm::mat4 rotMatrix = glm::mat4(1.0f);
    if (angle != 0 && !glm::isnan(angle))
    {
        rotMatrix = glm::rotate(rotMatrix, angle, glm::normalize(axis));
    }

    return rotMatrix;
}

void Fish::draw(glm::mat4 MVMatrix, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, GLint uMVMatrixLocation, GLint uMVProjMatrixLocarion, GLint uNormalMatrixLocation, Geometry shape, GLuint texture, GLenum DRAW_MODE) {

    MVMatrix = glm::scale(MVMatrix, glm::vec3(this->size(), this->size(), this->size()));
    MVMatrix = glm::translate(MVMatrix, this->position());
    glm::mat4 rotMatrix = this->getRotationMatrix();
    MVMatrix = MVMatrix * rotMatrix;

    glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uMVProjMatrixLocarion, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
    glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));    
    
    glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(DRAW_MODE, 0, shape.getVertexCount());
    glBindTexture(GL_TEXTURE_2D, 0);

}



std::vector<Fish> createHerd(const unsigned int fishNumber, double AREA, double SPEED) {
    std::vector<Fish> fishherd;
    for (unsigned int i = 0; i < fishNumber; ++i) {
        double size = .4;
        glm::vec3 position = glm::vec3(glm::linearRand(-AREA, AREA), glm::linearRand(-AREA, AREA), glm::linearRand(-AREA, AREA));
        glm::vec3 angle = glm::vec3(0, 0, -1);
        double speed = SPEED;
        fishherd.push_back(Fish(position, angle, speed, size, i));
    }
    return fishherd;
}

}