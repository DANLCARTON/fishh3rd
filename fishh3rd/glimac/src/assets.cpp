#include "glimac/assets.hpp"
#include "glimac/fish.hpp"
#include "glimac/Geometry.hpp"
#include "glimac/Image.hpp"

namespace glimac {

    void importTexture(std::unique_ptr<Image> &image, GLuint &skin) {
        glGenTextures(1, &skin);
        glBindTexture(GL_TEXTURE_2D, skin);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}