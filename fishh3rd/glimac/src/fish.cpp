#include "glimac/fish.hpp"

namespace glimac {

double getAngle(double a, double b) {   
    return b > 0 ? std::acos(a) : -std::acos(a);
}

void Fish::move(const SDLWindowManager &wm) {
    // MVMatrix = glm::translate(MVMatrix, this->angle()*(wm.getTime()+1));
    this->position(this->position()+(this->angle()*glm::vec3(this->speed())));
    // std::cout << this->position() << this->angle() << std::endl;
}

void Fish::turn(int axis, int dir, double str, double TURN_FACTOR) {

    // std::cout << str << std::endl;

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

void Fish::draw(glm::mat4 MVMatrix, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, GLint uMVMatrixLocation, GLint uMVProjMatrixLocarion, GLint uNormalMatrixLocation, Geometry shape, GLuint texture) {

    //std::cout << this->position() << std::endl;

    MVMatrix = glm::scale(MVMatrix, glm::vec3(this->size(), this->size(), this->size()));
    // MVMatrix            = glm::translate(glm::mat4(1.0f), this->position());
    MVMatrix = glm::translate(MVMatrix, this->position());
    glm::mat4 rotMatrix = this->getRotationMatrix();
    MVMatrix            = MVMatrix * rotMatrix;
    //MVMatrix = glm::translate(MVMatrix, this->position());
    //MVMatrix = glm::rotate(MVMatrix, 1.f, this->angle());

    glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uMVProjMatrixLocarion, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
    glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));    

    //glDrawArrays(GL_TRIANGLES, 0, this->shape().getVertexCount());
    //glDrawElements(GL_TRIANGLES, shape.getIndexCount(), GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_TRIANGLES, shape.getVertexCount(), GL_UNSIGNED_INT, NULL);
    
    glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(GL_TRIANGLE_FAN, 0, shape.getVertexCount());
    glBindTexture(GL_TEXTURE_2D, 0);

}

}