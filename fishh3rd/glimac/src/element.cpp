#include "glimac/element.hpp"
#include <iostream>

namespace glimac {

    void Element::draw(glm::mat4 MVMatrix, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, GLint uMVMatrixLocation, GLint uMVProjMatrixLocation, GLint uNormalMatrixLocation, Geometry shape, GLuint texture) {

        MVMatrix = glm::translate(MVMatrix, this->m_position);
        MVMatrix = glm::scale(MVMatrix, this->m_size);
        MVMatrix = glm::rotate(MVMatrix, 1.0f, this->m_angle);

        glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uMVProjMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
        glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));    
        
        glBindTexture(GL_TEXTURE_2D, texture);
            glDrawArrays(GL_TRIANGLE_FAN, 1, shape.getVertexCount());
            //glDrawArrays(GL_LINE_STRIP, 1, shape.getVertexCount());
        glBindTexture(GL_TEXTURE_2D, 0);

    }
}