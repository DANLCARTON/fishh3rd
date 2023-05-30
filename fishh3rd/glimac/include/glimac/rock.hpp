#pragma once

#include <vector>
#include <glimac/Sphere.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Geometry.hpp>

#include "common.hpp"

namespace glimac {

    class Rock {
    public:
        glm::vec3 m_position;
        glm::vec3 m_angle;
        glm::vec3 m_size;
        Geometry m_shape;

        Rock();
        Rock(glm::vec3 position, glm::vec3 angle, glm::vec3 size, Geometry shape) : m_position(position), m_angle(angle), m_size(size), m_shape(shape) {}
        ~Rock() = default;

        void draw(glm::mat4 MVMatrix, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, GLint uMVMatrixLocation, GLint uMVProjMatrixLocarion, GLint uNormalMatrixLocation, Geometry shape, GLuint texture);
        
    };    

    std::vector<Rock> createRocks(std::vector<Geometry> &rockShapes);
}