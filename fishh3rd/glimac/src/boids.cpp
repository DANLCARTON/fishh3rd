#include "glimac/boids.hpp"
#include "glimac/fish.hpp"

namespace glimac {

int sign(float value) {
    return value >= 0 ? 1 : -1;
}

double distance(Fish &fish, Fish &otherFish) {
    double distanceX = otherFish.position()[0] - fish.position()[0];
    double distanceY = otherFish.position()[1] - fish.position()[1];
    double distanceZ = otherFish.position()[2] - fish.position()[2];
    double distance = std::sqrt(distanceX*distanceX + distanceY*distanceY + distanceZ*distanceZ);
    return distance;
}

// - - - - - - G R O S S E S   F O N C T I O N S - - - - - -

void separation(Fish &fish, Fish &otherFish, double SEPARATION_RADIUS, double SEPARATION_STRENGTH, double TURN_FACTOR) {
    float dist = distance(fish, otherFish);
    glm::vec3 distanceVec = otherFish.position()-fish.position();
    glm::vec3 diffAngle = fish.angle()-otherFish.angle();

    int directionXY = sign(diffAngle[2]);
    int directionXZ = sign(diffAngle[1]);

    if (distanceVec[0] < SEPARATION_RADIUS || distanceVec[1] < SEPARATION_RADIUS) {
        otherFish.turn(1, directionXY, 1/(dist*SEPARATION_STRENGTH), TURN_FACTOR);
    }
    if (distanceVec[1] < SEPARATION_RADIUS || distanceVec[2] < SEPARATION_RADIUS) {
        otherFish.turn(2, directionXZ, 1/(dist*SEPARATION_STRENGTH), TURN_FACTOR);
    }
}

void alignment(Fish &fish, Fish &otherFish, double SEPARATION_RADIUS, double ALIGNMENT_RADIUS, double ALIGNMENT_STRENGTH, double TURN_FACTOR) {
    float dist = distance(fish, otherFish);
    glm::vec3 distanceVec = otherFish.position()-fish.position();
    glm::vec3 diffAngle = fish.angle()-otherFish.angle();

    int directionXY = sign(diffAngle[2]);
    int directionXZ = sign(diffAngle[1]);

    if (
        (SEPARATION_RADIUS < distanceVec[0] && distanceVec[0] < ALIGNMENT_RADIUS) ||
        (SEPARATION_RADIUS < distanceVec[1] && distanceVec[1] < ALIGNMENT_RADIUS)
    ) {
        otherFish.turn(1, -directionXY, 1/(dist*ALIGNMENT_STRENGTH), TURN_FACTOR);
    }

    if (
        (SEPARATION_RADIUS < distanceVec[1] && distanceVec[1] < ALIGNMENT_RADIUS) ||
        (SEPARATION_RADIUS < distanceVec[2] && distanceVec[2] < ALIGNMENT_RADIUS)
    ) {
        otherFish.turn(2, -directionXZ, 1/(dist*ALIGNMENT_STRENGTH), TURN_FACTOR);
    }
}

void cohesion(Fish &fish, std::vector<Fish> &fishherd, double COHESION_RADIUS, double COHESION_STRENGTH, double TURN_FACTOR) {
    double averageXYDirection = 0;
    double averageXZDirection = 0;
    double fishesInTheRadius = 0;

    for (Fish &otherFish : fishherd) {
        if (distance(fish, otherFish) < COHESION_RADIUS) {
            averageXYDirection += getAngle(otherFish.angle()[0], otherFish.angle()[1]);
            averageXZDirection += getAngle(otherFish.angle()[0], otherFish.angle()[2]);
            ++fishesInTheRadius;
        }
    }

    averageXYDirection = averageXYDirection/fishesInTheRadius;
    averageXZDirection = averageXZDirection/fishesInTheRadius;

    fish.turn(1, averageXYDirection, COHESION_STRENGTH, TURN_FACTOR);
    fish.turn(2, averageXZDirection, COHESION_STRENGTH, TURN_FACTOR);
}



}