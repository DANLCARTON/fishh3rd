#include "glimac/rock.hpp"

namespace glimac {

void Rock::draw(glm::mat4 MVMatrix, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, GLint uMVMatrixLocation, GLint uMVProjMatrixLocation, GLint uNormalMatrixLocation, Geometry shape, GLuint texture) {

    MVMatrix = glm::scale(MVMatrix, this->m_size);
    MVMatrix = glm::translate(MVMatrix, this->m_position);
    MVMatrix = glm::rotate(MVMatrix, 1.f, this->m_angle);

    glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uMVProjMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
    glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));    
    
    glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(GL_TRIANGLE_FAN, 0, shape.getVertexCount());
    glBindTexture(GL_TEXTURE_2D, 0);

}

std::vector<Rock> createRocks(std::vector<Geometry> &rockShapes) {
    std::vector<Rock> rockHerd;
    rockHerd.push_back(Rock(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 1.f, 1.f), rockShapes[0]));
    return rockHerd;
}

}