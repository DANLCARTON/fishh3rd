#pragma once

#include <vector>
#include <glimac/trackBallCamera.hpp>
#include <glimac/fish.hpp>
#include <glimac/glm.hpp>

#include "common.hpp"

namespace glimac {

    void SDLinputs(SDLWindowManager &windowManager, double TURN_FACTOR, Camera &camera, Fish &playerFish, SDL_Event &e);

}