#ifndef TRACKBALLCAMERA
#define TRACKBALLCAMERA

#include <glimac/glm.hpp>

namespace glimac {

class Camera {
    private :
        float m_distance;
        float m_fAngleX;
        float m_fAngleY;
    public: 
        Camera(float distance = 5, float angleX = 0, float angleY = 0) {this->m_distance = distance; this->m_fAngleX = angleX; this->m_fAngleY = angleY;};
        ~Camera() = default;

        float getDistance() {return this->m_distance;};

        void moveFront(float delta);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        glm::mat4 getViewMatrix() const;
};

}

#endif