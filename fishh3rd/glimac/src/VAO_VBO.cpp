#include "glimac/VAO_VBO.hpp"
#include "glimac/Geometry.hpp"

namespace glimac {

    void createVAO(GLuint &vao, GLuint &vbo) {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

            const GLuint VERTEX_ATTR_POSITION=0;
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

            const GLuint VERTEX_ATTR_NORMAL=1;
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

            const GLuint VERTEX_ATTR_TEXTURE=2;
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

            glBindBuffer(GL_ARRAY_BUFFER,vbo);
                glVertexAttribPointer(VERTEX_ATTR_POSITION, 
                    3, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),0);
                glVertexAttribPointer(VERTEX_ATTR_NORMAL,
                    3, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),(void*) (sizeof(glm::vec3)));
                glVertexAttribPointer(VERTEX_ATTR_TEXTURE,
                    2, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),(void*) (2*sizeof(glm::vec3)));
            glBindBuffer(GL_ARRAY_BUFFER,0);

        glBindVertexArray(0);
    }

    void createVBO(GLuint &vbo, Geometry &mesh) {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            std::vector<float> vertex_data;
            glBufferData(GL_ARRAY_BUFFER, sizeof(Geometry::Vertex) * mesh.getVertexCount(), mesh.getVertexBuffer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}