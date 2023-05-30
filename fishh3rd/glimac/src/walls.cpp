#include "glimac/walls.hpp"
#include "glimac/fish.hpp"
#include "glimac/boids.hpp"

namespace glimac {

/*void avoidWall(Fish &fish, double distance, const int wall) {

    // double str = WALLS_STRENGTH*(1/(distance));
    // double str = WALLS_STRENGTH*std::exp(-distance);
    double str = 20;
    std::cout << fish.id << " " << distance << " " << wall << " " << str <<  std::endl;
    // std::cout << WALLS_STRENGTH << "  " << distance << std::endl;
 
    int dir = sign(wall);
    if (wall == 1 || wall == -1) { // x ou -x
        if (std::abs(fish.angle()[1]) > std::abs(fish.angle()[2])) { // y > z
            fish.turn(2, sign(fish.angle()[1])*dir, str);
            //if (dir == sign(fish.angle()[0])) fish.turn(2, sign(fish.angle()[1])*dir, str);
        } else {
            fish.turn(1, sign(fish.angle()[2])*dir, str);
            //if (dir == sign(fish.angle()[0])) fish.turn(1, sign(fish.angle()[2])*dir, str);
        }
    } else if (wall == 2 || wall == -2) { // y ou -y
        if (std::abs(fish.angle()[0]) > std::abs(fish.angle()[2])) { // x > z
            fish.turn(1, sign(fish.angle()[0])*dir, str);
            //if (dir == sign(fish.angle()[1])) fish.turn(1, sign(fish.angle()[0])*dir, str);
        } else {
            fish.turn(0, sign(fish.angle()[2])*dir, str);
            //if (dir == sign(fish.angle()[1])) fish.turn(0, sign(fish.angle()[2])*dir, str);
        }
    } else if (wall == 3 || wall == -3) { // z ou -z
        if (std::abs(fish.angle()[0]) > std::abs(fish.angle()[1])) { // x > y
            fish.turn(2, sign(fish.angle()[0])*dir, str);
            //if (dir == sign(fish.angle()[2])) fish.turn(2, sign(fish.angle()[0])*dir, str);
        } else {
            fish.turn(0, sign(fish.angle()[1])*dir, str);
            //if (dir == sign(fish.angle()[2])) fish.turn(0, sign(fish.angle()[1])*dir, str);
        }
    } else {
        ;
    }
}
*/

// fish : position, angle, speed, size, shape, id

void avoidWall(Fish &wallFish, Fish &fish, double WALLS_RADIUS, double WALLS_STRENGTH, double TURN_FACTOR) {

    float dist = distance(wallFish, fish);
    glm::vec3 distanceVec = fish.position()-wallFish.position();
    glm::vec3 diffAngle = wallFish.angle()-fish.angle();

    int directionXY = sign(diffAngle[2]);
    int directionXZ = sign(diffAngle[1]);

    if ((distanceVec[0] < WALLS_RADIUS) || (distanceVec[1] < WALLS_RADIUS)) {
        fish.turn(1, -directionXY, 1/(dist*.2*WALLS_STRENGTH), TURN_FACTOR);
    }

    if ((distanceVec[1] < WALLS_RADIUS) ||(distanceVec[2] < WALLS_RADIUS)) {
        fish.turn(2, -directionXZ, 1/(dist*.2*WALLS_STRENGTH), TURN_FACTOR);
    }
}

void wall(Fish &fish, double distance, const int wall, double AREA, double WALLS_RADIUS, double WALLS_STRENGTH, double TURN_FACTOR) {
    Fish wallFish = Fish(
        glm::vec3(fish.position()),
        glm::vec3(0),
        0, 0, Sphere(0, 0, 0), 1000
    );
    if (wall == 1) {
        wallFish.position(glm::vec3(AREA, fish.position()[1], fish.position()[2]));
        //wallFish.position(glm::vec3(AREA, 0, 0));
        wallFish.angle(glm::vec3(-1, 0, 0));
    } else if (wall == -1) {
        wallFish.position(glm::vec3(-AREA, fish.position()[1], fish.position()[2]));
        //wallFish.position(glm::vec3(-AREA, 0, 0));
        wallFish.angle(glm::vec3(1, 0, 0));
    } else if (wall == 2) {
        wallFish.position(glm::vec3(fish.position()[0], AREA, fish.position()[2]));
        //wallFish.position(glm::vec3(0, AREA, 0));
        wallFish.angle(glm::vec3(0, -1, 0));
    } else if (wall == -2) {
        wallFish.position(glm::vec3(fish.position()[0], -AREA, fish.position()[2]));
        //wallFish.position(glm::vec3(0, -AREA, 0));
        wallFish.angle(glm::vec3(0, 1, 0));
    } else if (wall == 3) {
        wallFish.position(glm::vec3(fish.position()[0], fish.position()[1], AREA));
        //wallFish.position(glm::vec3(0, 0, -AREA));
        wallFish.angle(glm::vec3(0, 0, -1));
    } else if (wall == -3) {
        wallFish.position(glm::vec3(fish.position()[0], fish.position()[1], -AREA));
        //wallFish.position(glm::vec3(0, 0, AREA));
        wallFish.angle(glm::vec3(0, 0, 1));
    } else {
        return;
    }
    avoidWall(wallFish, fish, WALLS_RADIUS, WALLS_STRENGTH, TURN_FACTOR);
}

void wallSeparation(Fish &fish, double AREA, double WALLS_RADIUS, double WALLS_STRENGTH, double TURN_FACTOR) {
    double rightWallDistance = AREA-fish.position()[0];
    double leftWallDistance = fish.position()[0]+AREA;
    double topWallDistance = AREA-fish.position()[1];
    double bottomWallDistance = fish.position()[1]+AREA;
    double backWallDistance = AREA-fish.position()[2];
    double frontWallDistance = fish.position()[2]+AREA;

    if (rightWallDistance < WALLS_RADIUS) wall(fish, rightWallDistance, 1, AREA, WALLS_RADIUS, WALLS_STRENGTH, TURN_FACTOR);
    if (leftWallDistance < WALLS_RADIUS) wall(fish, leftWallDistance, -1, AREA, WALLS_RADIUS, WALLS_STRENGTH, TURN_FACTOR);
    if (topWallDistance < WALLS_RADIUS) wall(fish, topWallDistance, 2, AREA, WALLS_RADIUS, WALLS_STRENGTH, TURN_FACTOR);
    if (bottomWallDistance < WALLS_RADIUS) wall(fish, bottomWallDistance, -2, AREA, WALLS_RADIUS, WALLS_STRENGTH, TURN_FACTOR);
    if (backWallDistance < WALLS_RADIUS) wall(fish, backWallDistance, 3, AREA, WALLS_RADIUS, WALLS_STRENGTH, TURN_FACTOR);
    if (frontWallDistance < WALLS_RADIUS) wall(fish, frontWallDistance, -3, AREA, WALLS_RADIUS, WALLS_STRENGTH, TURN_FACTOR);
}

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