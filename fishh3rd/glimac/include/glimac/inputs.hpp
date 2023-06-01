#pragma once

#include <vector>
#include <glimac/trackBallCamera.hpp>
#include <glimac/fish.hpp>
#include <glimac/glm.hpp>

#include "common.hpp"

namespace glimac {

    GLenum switchDrawMode(GLenum DRAW_MODE);

    void SDLinputs(
        SDLWindowManager &windowManager, 
        double &TURN_FACTOR, 
        double &SEPARATION_RADIUS, 
        double &ALIGNMENT_RADIUS, 
        double &COHESION_RADIUS, 
        double &SEPARATION_STRENGTH, 
        double &ALIGNMENT_STRENGTH, 
        double &COHESION_STRENGTH, 
        float &R_LIGHT, 
        float &G_LIGHT, 
        float &B_LIGHT, 
        GLenum &DRAW_MODE, 
        Camera &camera, 
        Fish &playerFish, 
        SDL_Event &e
    );

    void displayParameters(
        double &TURN_FACTOR, 
        double &SEPARATION_RADIUS, 
        double &ALIGNMENT_RADIUS, 
        double &COHESION_RADIUS, 
        double &SEPARATION_STRENGTH, 
        double &ALIGNMENT_STRENGTH, 
        double &COHESION_STRENGTH, 
        float &R_LIGHT, 
        float &G_LIGHT, 
        float &B_LIGHT, 
        GLenum &DRAW_MODE
    );

}