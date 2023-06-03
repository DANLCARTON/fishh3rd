#pragma once

#include <vector>
#include <glimac/Sphere.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Geometry.hpp>

#include "common.hpp"

namespace glimac {

    class Fish {
        private:
            glm::vec3 m_position;
            glm::vec3 m_angle;
            double m_speed;
            double m_size;

        public:
            unsigned int id;

            Fish();
            Fish(glm::vec3 position, glm::vec3 angle, double speed, double size, unsigned int id) : m_position(position), m_angle(angle), m_speed(speed), m_size(size), id(id) {}
            ~Fish() = default;
            
            glm::vec3 position() {return this->m_position;};
            void position(glm::vec3 newPosition) {m_position = newPosition;};   
            glm::vec3 angle() {return this->m_angle;};
            void angle(glm::vec3 newAngle) {m_angle = newAngle;};
            double speed() {return this->m_speed;};
            void speed(double newSpeed) {m_speed = newSpeed;};
            double size() {return this->m_size;};
            void size(double newSize) {m_size = newSize;};

            void move(const SDLWindowManager &wm);
            void turn(int axis, int dir, double str, double TURN_FACTOR);
            void draw(glm::mat4 MVMatrix, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, GLint uMVMatrixLocation, GLint uMVProjMatrixLocarion, GLint uNormalMatrixLocation, Geometry shape, GLuint texture, GLenum DRAW_MODE);
            glm::mat4 getRotationMatrix() const;
    };

    double getAngle(double a, double b);

    std::vector<Fish> createHerd(const unsigned int fishNumber, double AREA, double SPEED);
    
}