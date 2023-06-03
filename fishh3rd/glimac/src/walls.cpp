#include "glimac/walls.hpp"
#include "glimac/fish.hpp"
#include "glimac/boids.hpp"

namespace glimac {

// y'a très certainement mieux à faire mais ça fera le taf pour l'instant. 
void passTrough(Fish &fish, double AREA) {
    const double realFishArea = (AREA+20)*(fish.size()+.1);
    if (fish.position()[0] >= realFishArea || fish.position()[0] <= -realFishArea) {
        fish.position(glm::vec3(-fish.position()[0]+sign(fish.position()[0])*3, fish.position()[1], fish.position()[2]));
    }
    if (fish.position()[1] >= realFishArea || fish.position()[1] <= -realFishArea) {
        fish.position(glm::vec3(fish.position()[0], -fish.position()[1]+sign(fish.position()[1])*3, fish.position()[2]));
    }
    if (fish.position()[2] >= realFishArea || fish.position()[2] <= -realFishArea) {
        fish.position(glm::vec3(fish.position()[0], fish.position()[1], -fish.position()[2]+sign(fish.position()[2])*3));
    }
}
}