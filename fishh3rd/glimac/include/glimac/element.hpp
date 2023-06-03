#pragma once

#include <vector>
#include <glimac/Sphere.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Geometry.hpp>

#include "common.hpp"

namespace glimac {

    class Element {
    public:
        glm::vec3 m_position;
        glm::vec3 m_angle;
        glm::vec3 m_size;
        Geometry m_shape;
        GLuint m_vao;
        GLuint m_texture;

        Element();
        Element(glm::vec3 position, glm::vec3 angle, glm::vec3 size, Geometry shape, GLuint vao, GLuint texture) : m_position(position), m_angle(angle), m_size(size), m_shape(shape), m_vao(vao), m_texture(texture) {}
        ~Element() = default;

        void draw(glm::mat4 MVMatrix, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, GLint uMVMatrixLocation, GLint uMVProjMatrixLocarion, GLint uNormalMatrixLocation, Geometry shape, GLuint texture);
        
    };    
}