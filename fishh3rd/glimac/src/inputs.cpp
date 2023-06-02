#include "glimac/inputs.hpp"
#include "glimac/SDLWindowManager.hpp"
#include "glimac/trackBallCamera.hpp"
#include "glimac/fish.hpp"
#include "glimac/glm.hpp"
#include <iostream>

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

    std::string getLOD(GLenum DRAW_MODE) {
        if (DRAW_MODE == GL_TRIANGLE_FAN) return "HIGH";
        else return "LOW";
        return "HIGH";
    }

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
    ) {
        std::cout << " - A C T   O N   T H E   F I S H   H 3 R D ! - " << std::endl << std::endl;
        std::cout << "Rotation intensity: " << "   C <- " << TURN_FACTOR << " -> V" << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "Separation radius: " << "    T <- " << SEPARATION_RADIUS << " -> Y" << std::endl;
        std::cout << "Alignment radius: " << "     G <- " << ALIGNMENT_RADIUS << " -> H" << std::endl;
        std::cout << "Cohesion radius: " << "      B <- " << COHESION_RADIUS << " -> N" << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "Separation strength: " << "  U <- " << SEPARATION_STRENGTH << " -> I" << std::endl;
        std::cout << "Alignment strength: " << "   J <- " << ALIGNMENT_STRENGTH << " -> K" << std::endl;
        std::cout << "Cohesion strength: " << "    , <- " << COHESION_STRENGTH << " -> ;" << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "Red light: " << "            O <- " << R_LIGHT << " -> P" << std::endl;
        std::cout << "Green light: " << "          L <- " << G_LIGHT << " -> M" << std::endl;
        std::cout << "Blue light: " << "           : <- " << B_LIGHT << " -> !" << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "Level of details: " << "     Space <- " << getLOD(DRAW_MODE) << std::endl << std::endl;
        std::cout << " - M O V E   T H E   C A M E R A ! - " << std::endl << std::endl;
        std::cout << "Rotate:  Q <-    -> D" << std::endl;
        std::cout << "Tilt:    Z ^      v S" << std::endl;
        std::cout << "Zoom:    R ^      v F" << std::endl << std::endl;
        std::cout << " - M O V E   Y O U R   F I S H ! - " << std::endl << std::endl;
        std::cout << "Rotate:  left arrow <-     -> right arrow" << std::endl;
        std::cout << "Tilt:      up arrow <-     -> back arrow" << std::endl;
        std::cout << "\x1B[2J\x1B[H";
    }

    GLenum switchDrawMode(GLenum DRAW_MODE) {
        if (DRAW_MODE == GL_TRIANGLE_FAN) return GL_LINE_STRIP;
        else return GL_TRIANGLE_FAN;
        return GL_TRIANGLE_FAN;
    }

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
    ) {
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
                // paramètres de la simulation parce que j'arrive pas à implémenter une GUI alors que c'est soi-disant facile à implémenter je vais me foutre en l'air sérieux
                case SDLK_t:
                    if (SEPARATION_RADIUS >= 1) --SEPARATION_RADIUS;
                    break;
                case SDLK_y:
                    ++SEPARATION_RADIUS;
                    break;
                case SDLK_g:
                    if (ALIGNMENT_RADIUS >= 1) --ALIGNMENT_RADIUS;
                    break;
                case SDLK_h:
                    ++ALIGNMENT_RADIUS;
                    break;
                case SDLK_b:
                    if (COHESION_RADIUS >= 1) --COHESION_RADIUS;
                    break;
                case SDLK_n:
                    ++COHESION_RADIUS;
                    break;
                case SDLK_u:
                    if (SEPARATION_STRENGTH >= 2) --SEPARATION_STRENGTH;
                    break;
                case SDLK_i:
                    ++SEPARATION_STRENGTH;
                    break;
                case SDLK_j:
                    if (ALIGNMENT_STRENGTH >= 2) --ALIGNMENT_STRENGTH;
                    break;
                case SDLK_k:
                    ++ALIGNMENT_STRENGTH;
                    break;
                case SDLK_COMMA:
                    if (COHESION_STRENGTH >= 2) --COHESION_STRENGTH;
                    break;
                case SDLK_SEMICOLON:
                    ++COHESION_STRENGTH;
                    break;
                case SDLK_o:
                    if (R_LIGHT >= 1) --R_LIGHT;
                    break;
                case SDLK_p:
                    ++R_LIGHT;
                    break;
                case SDLK_l:
                    if (G_LIGHT >= 1) --G_LIGHT;
                    break;
                case SDLK_m:
                    ++G_LIGHT;
                    break;
                case SDLK_COLON:
                    if (B_LIGHT >= 1) --B_LIGHT;
                    break;
                case SDLK_EXCLAIM:
                    ++B_LIGHT;
                    break;
                case SDLK_c:
                    if (TURN_FACTOR >= 0.005) TURN_FACTOR -= 0.005;
                    break;
                case SDLK_v:
                    TURN_FACTOR += 0.005;
                    break;
                case SDLK_SPACE:    
                    DRAW_MODE = switchDrawMode(DRAW_MODE);
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