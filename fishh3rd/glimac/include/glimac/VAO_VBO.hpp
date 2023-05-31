#pragma once

#include <vector>
#include <glimac/Geometry.hpp>

#include "common.hpp"

namespace glimac {

    void createVAO(GLuint &vao, GLuint &vbo);
    void createVBO(GLuint &vbo, Geometry &mesh);
    void createIBO(GLuint &ibo, Geometry &mesh);
    void createVAOfromIBO(GLuint &vao, GLuint &ibo);

}