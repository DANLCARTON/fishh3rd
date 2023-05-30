#pragma once

#include <vector>
#include <glimac/Sphere.hpp>
#include <glimac/fish.hpp>
#include <glimac/boids.hpp>

#include "common.hpp"

namespace glimac {

    void avoidWall(Fish &wallFish, Fish &fish, double WALLS_RADIUS, double WALLS_STRENGTH, double TURN_FACTOR);
    void wall(Fish &fish, double distance, const int wall, double AREA, double WALLS_RADIUS, double WALLS_STRENGTH, double TURN_FACTOR);
    void wallSeparation(Fish &fish, double AREA, double WALLS_RADIUS, double WALLS_STRENGTH, double TURN_FACTOR);
    void passTrough(Fish &fish, double AREA);

}