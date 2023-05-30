#pragma once

#include <vector>
#include <glimac/Sphere.hpp>
#include <glimac/fish.hpp>

#include "common.hpp"

namespace glimac {

    int sign(float value);
    double distance(Fish &fish, Fish &otherFish);
    void separation(Fish &fish, Fish &otherFish, double SEPARATION_RADIUS, double SEPARATION_STRENGTH, double TURN_FACTOR);
    void alignment(Fish &fish, Fish &otherFish, double SEPARATION_RADIUS, double ALIGNMENT_RADIUS, double ALIGNMENT_STRENGTH, double TURN_FACTOR);
    void cohesion(Fish &fish, std::vector<Fish> &fishherd, double COHESION_RADIUS, double COHESION_STRENGTH, double TURN_FACTOR);

}