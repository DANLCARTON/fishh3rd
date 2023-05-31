#include "glimac/inputs.hpp"
#include "glimac/SDLWindowManager.hpp"
#include "glimac/trackBallCamera.hpp"
#include "glimac/fish.hpp"
#include "glimac/glm.hpp"

namespace glimac {

    // gestion des inputs pour le fish doré
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;

    // gestion des imputs clavier pour la caméra
    bool camUp = false;
    bool camDown = false;
    bool camLeft = false;
    bool camRight = false;
    bool camFront = false;
    bool camBack = false;

    void SDLinputs(SDLWindowManager &windowManager, double TURN_FACTOR, Camera &camera, Fish &playerFish, SDL_Event &e) {
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                // fish doré
                case SDLK_UP:
                    moveDown = true;
                    break;
                case SDLK_DOWN:
                    moveUp = true;
                    break;
                case SDLK_LEFT:
                    moveLeft = true;
                    break;
                case SDLK_RIGHT:
                    moveRight = true;
                    break;
                // camera clavier
                case SDLK_z:
                    camUp = true;
                    break;
                case SDLK_s:    
                    camDown = true;
                    break;
                case SDLK_q:
                    camLeft = true;
                    break;
                case SDLK_d:
                    camRight = true;
                    break;
                case SDLK_r:
                    camFront = true;
                    break;
                case SDLK_f:
                    camBack = true;
                    break;
            }
        } else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                // fish doré
                case SDLK_UP:
                    moveDown = false;
                    break;
                case SDLK_DOWN:
                    moveUp = false;
                    break;
                case SDLK_LEFT:
                    moveLeft = false;
                    break;
                case SDLK_RIGHT:
                    moveRight = false;
                // camera clavier
                case SDLK_z:
                    camUp = false;
                    break;
                case SDLK_s:
                    camDown = false;
                    break;
                case SDLK_q:
                    camLeft = false;
                    break;
                case SDLK_d:
                    camRight = false;
                    break;
                case SDLK_r:
                    camFront = false;
                    break;
                case SDLK_f:
                    camBack = false;
                    break;
            }
        } 

        // par contre ça en vrai ça peut rester là
        if (moveUp) {
            playerFish.turn(0, 1, 10, TURN_FACTOR);
        }

        if (moveDown) {
            playerFish.turn(0, -1, 10, TURN_FACTOR);
        }

        if (moveLeft) {
            playerFish.turn(2, -1, 10, TURN_FACTOR);
        }

        if (moveRight) {
            playerFish.turn(2, 1, 10, TURN_FACTOR);
        }

        if (camFront) {
            camera.moveFront(-.1);
        }

        if (camBack) {
            camera.moveFront(.1);
        }

        if (camUp) {
            camera.rotateUp(1);
        }

        if (camDown) {
            camera.rotateUp(-1);
        }

        if (camLeft) {
            camera.rotateLeft(1);
        }

        if (camRight) {
            camera.rotateLeft(-1);
        }
    }
}