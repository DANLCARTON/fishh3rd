#define GLM_FORCE_RADIANS
#define TINYOBJLOADER_IMPLEMENTATION
//#include "../glimac/src/tiny_obj_loader.h"
#include "glm/detail/type_mat.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Geometry.hpp>
#include <math.h>
#include <SDL/SDL.h>
#include <glimac/trackBallCamera.hpp>

//                                                         BEST VALUES
const unsigned int FISH_NUMBER = 150; //                    peu, entre 10 et 15 ça me semble pas mal ?
const double AREA = 30.f; //                                    20.f
const double TURN_FACTOR = .005; //                         0.01
const double SEPARATION_RADIUS = 5; //                     10
const double SEPARATION_STRENGTH = 1; //                    1
const double ALIGNMENT_RADIUS = 10; //                      10
const double ALIGNMENT_STRENGTH = 1; //                       1
const double COHESION_RADIUS = 15; //                     15
const double COHESION_STRENGTH = 1; //                        1
const double WALLS_RADIUS = 20; //                            5
const double WALLS_STRENGTH = 1; //                        1
const double SPEED = 0.15; //                                 .15


// - - - - - FISH CLASS - - - - - -



using namespace glimac;

class Fish {
    private:
        glm::vec3 m_position;
        glm::vec3 m_angle;
        double m_speed;
        double m_size;
        Sphere m_shape;

    public:
        unsigned int id;

        Fish();
        Fish(glm::vec3 position, glm::vec3 angle, double speed, double size, const Sphere &shape, unsigned int id) : m_position(position), m_angle(angle), m_speed(speed), m_size(size), m_shape(shape), id(id) {}
        ~Fish() = default;
        
        glm::vec3 position() {return this->m_position;};
        void position(glm::vec3 newPosition) {m_position = newPosition;};
        glm::vec3 angle() {return this->m_angle;};
        void angle(glm::vec3 newAngle) {m_angle = newAngle;};
        double speed() {return this->m_speed;};
        void speed(double newSpeed) {m_speed = newSpeed;};
        double size() {return this->m_size;};
        void size(double newSize) {m_size = newSize;};
        Sphere shape() {return this->m_shape;};
        void shape(Sphere newShape) {m_shape = newShape;};

        glm::mat4 move(glm::mat4 MVMatrix, const SDLWindowManager &wm);
        void turn(int axis, int dir, double str);
        void draw(glm::mat4 MVMatrix, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, GLint uMVMatrixLocation, GLint uMVProjMatrixLocarion, GLint uNormalMatrixLocation, Geometry shape, GLuint texture);
};

// - - - - - - P E T I T E S   F O N C T I O N S - - - - - -

int sign(float value) {
    return value >= 0 ? 1 : -1;
}

double getAngle(double a, double b) {   
    return b > 0 ? std::acos(a) : -std::acos(a);
}

std::vector<Fish> createHerd(const unsigned int fishNumber) {
    std::vector<Fish> fishherd;
    for (unsigned int i = 0; i < fishNumber; ++i) {
        double size = .2;
        // glm::vec3 position = glm::vec3(glm::linearRand(-1.f/size, 1.f/size), glm::linearRand(-1.f/size, 1.f/size), glm::linearRand(-1.f/size, 1.f/size));
        glm::vec3 position = glm::vec3(glm::linearRand(-AREA, AREA), glm::linearRand(-AREA, AREA), glm::linearRand(-AREA, AREA));
        // std::cout << position << std::endl;
        // glm::vec3 angle = glm::vec3(glm::sphericalRand(1.f));
        glm::vec3 angle = glm::vec3(0, 0, -1);
        double speed = SPEED;
        Sphere shape = Sphere(1.f, 32, 16);
        fishherd.push_back(Fish(position, angle, speed, size, shape, i));
    }
    return fishherd;
}

glm::mat4 Fish::move(glm::mat4 MVMatrix, const SDLWindowManager &wm) {
    // MVMatrix = glm::translate(MVMatrix, this->angle()*(wm.getTime()+1));
    this->position(this->position()+(this->angle()*glm::vec3(this->speed())));
    // std::cout << this->position() << this->angle() << std::endl;
    return MVMatrix;
}

void Fish::turn(int axis, int dir, double str) {

    // std::cout << str << std::endl;

    glm::vec3 newAngle;

    if (axis == 0) { // 0, 1, 1 | YZ
        double angle = getAngle(this->angle()[1], this->angle()[2]);
        angle += TURN_FACTOR*dir*str;
        newAngle = glm::vec3(this->angle()[0], std::cos(angle), std::sin(angle));
    } else if (axis == 1) { // 1, 1, 0 | XY
        double angle = getAngle(this->angle()[0], this->angle()[1]);
        angle += TURN_FACTOR*dir*str;
        newAngle = glm::vec3(std::cos(angle), std::sin(angle), this->angle()[2]);
    } else if (axis == 2) { // 1, 0, 1 | XZ
        double angle = getAngle(this->angle()[0], this->angle()[2]);
        angle += TURN_FACTOR*dir*str;
        newAngle = glm::vec3(std::cos(angle), this->angle()[1], std::sin(angle));
    } else {
        newAngle = glm::vec3(this->angle()[0], this->angle()[1], this->angle()[2]);
    }

    this->m_angle = newAngle;
}

void Fish::draw(glm::mat4 MVMatrix, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, GLint uMVMatrixLocation, GLint uMVProjMatrixLocarion, GLint uNormalMatrixLocation, Geometry shape, GLuint texture) {

    //std::cout << this->position() << std::endl;

    MVMatrix = glm::scale(MVMatrix, glm::vec3(this->size(), this->size(), this->size()));
    MVMatrix = glm::translate(MVMatrix, this->position());
    MVMatrix = glm::rotate(MVMatrix, 1.f, this->angle());

    glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uMVProjMatrixLocarion, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
    glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));    

    //glDrawArrays(GL_TRIANGLES, 0, this->shape().getVertexCount());
    //glDrawElements(GL_TRIANGLES, shape.getIndexCount(), GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_TRIANGLES, shape.getVertexCount(), GL_UNSIGNED_INT, NULL);
    
    glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(GL_TRIANGLE_FAN, 0, shape.getVertexCount());
    glBindTexture(GL_TEXTURE_2D, 0);

}

double distance(Fish &fish, Fish &otherFish) {
    double distanceX = otherFish.position()[0] - fish.position()[0];
    double distanceY = otherFish.position()[1] - fish.position()[1];
    double distanceZ = otherFish.position()[2] - fish.position()[2];
    double distance = std::sqrt(distanceX*distanceX + distanceY*distanceY + distanceZ*distanceZ);
    return distance;
}

// - - - - - - G R O S S E S   F O N C T I O N S - - - - - -

void separation(Fish &fish, Fish &otherFish) {
    float dist = distance(fish, otherFish);
    glm::vec3 distanceVec = otherFish.position()-fish.position();
    glm::vec3 diffAngle = fish.angle()-otherFish.angle();

    int directionXY = sign(diffAngle[2]);
    int directionXZ = sign(diffAngle[1]);

    if (distanceVec[0] < SEPARATION_RADIUS || distanceVec[1] < SEPARATION_RADIUS) {
        otherFish.turn(1, directionXY, 1/(dist*SEPARATION_STRENGTH));
    }
    if (distanceVec[1] < SEPARATION_RADIUS || distanceVec[2] < SEPARATION_RADIUS) {
        otherFish.turn(2, directionXZ, 1/(dist*SEPARATION_STRENGTH));
    }
}

void alignment(Fish &fish, Fish &otherFish) {
    float dist = distance(fish, otherFish);
    glm::vec3 distanceVec = otherFish.position()-fish.position();
    glm::vec3 diffAngle = fish.angle()-otherFish.angle();

    int directionXY = sign(diffAngle[2]);
    int directionXZ = sign(diffAngle[1]);

    if (
        (SEPARATION_RADIUS < distanceVec[0] && distanceVec[0] < ALIGNMENT_RADIUS) ||
        (SEPARATION_RADIUS < distanceVec[1] && distanceVec[1] < ALIGNMENT_RADIUS)
    ) {
        otherFish.turn(1, -directionXY, 1/(dist*ALIGNMENT_STRENGTH));
    }

    if (
        (SEPARATION_RADIUS < distanceVec[1] && distanceVec[1] < ALIGNMENT_RADIUS) ||
        (SEPARATION_RADIUS < distanceVec[2] && distanceVec[2] < ALIGNMENT_RADIUS)
    ) {
        otherFish.turn(2, -directionXZ, 1/(dist*ALIGNMENT_STRENGTH));
    }
}

void cohesion(Fish &fish, std::vector<Fish> &fishherd) {
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

    fish.turn(1, averageXYDirection, COHESION_STRENGTH);
    fish.turn(2, averageXZDirection, COHESION_STRENGTH);
}

// - - - - - - G E S T I O N   D E S   M U R S - - - - - -

/*
void avoidWall(Fish &fish, double distance, const int wall) {

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

void avoidWall(Fish &wallFish, Fish &fish) {

    float dist = distance(wallFish, fish);
    glm::vec3 distanceVec = fish.position()-wallFish.position();
    glm::vec3 diffAngle = wallFish.angle()-fish.angle();

    int directionXY = sign(diffAngle[2]);
    int directionXZ = sign(diffAngle[1]);

    if ((distanceVec[0] < WALLS_RADIUS) || (distanceVec[1] < WALLS_RADIUS)) {
        fish.turn(1, -directionXY, 1/(dist*.2*WALLS_STRENGTH));
    }

    if ((distanceVec[1] < WALLS_RADIUS) ||(distanceVec[2] < WALLS_RADIUS)) {
        fish.turn(2, -directionXZ, 1/(dist*.2*WALLS_STRENGTH));
    }
}

void wall(Fish &fish, double distance, const int wall) {
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
    avoidWall(wallFish, fish);
}

void wallSeparation(Fish &fish) {
    double rightWallDistance = AREA-fish.position()[0];
    double leftWallDistance = fish.position()[0]+AREA;
    double topWallDistance = AREA-fish.position()[1];
    double bottomWallDistance = fish.position()[1]+AREA;
    double backWallDistance = AREA-fish.position()[2];
    double frontWallDistance = fish.position()[2]+AREA;

    if (rightWallDistance < WALLS_RADIUS) wall(fish, rightWallDistance, 1);
    if (leftWallDistance < WALLS_RADIUS) wall(fish, leftWallDistance, -1);
    if (topWallDistance < WALLS_RADIUS) wall(fish, topWallDistance, 2);
    if (bottomWallDistance < WALLS_RADIUS) wall(fish, bottomWallDistance, -2);
    if (backWallDistance < WALLS_RADIUS) wall(fish, backWallDistance, 3);
    if (frontWallDistance < WALLS_RADIUS) wall(fish, frontWallDistance, -3);
}

// y'a très certainement mieux à faire mais ça fera le taf pour l'instant. 
void passTrough(Fish &fish) {
    const double realFishArea = AREA+20;
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

// - - - - - - M A I N - - - - - -

int main(int argc, char** argv) {

    Geometry FishMesh;
    FishMesh.loadOBJ("../assets/models/Fish.obj", "../assets/models/Fish.mtl");
    //FishMesh.loadOBJ("../assets/models/FishOriented.obj", "../assets/models/FishOriented.mtl");

    Geometry BGCube;
    BGCube.loadOBJ("../assets/models/cube.obj", "../assets/models/cube.mtl");

    //std::cout << (0 == -0) << std::endl;

    // Initialize SDL and open a window
    float width  = 1280;
    float height = 720; 
    SDLWindowManager windowManager(width, height, "✨𝐅𝐈𝐒𝐇𝐇𝟑𝐑𝐃✨");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************/
       // INITIALIZATION CODE

        // Initialize depth test
        // Permet de gérer les différents plans de la scène 
        glEnable(GL_DEPTH_TEST);

        /*
        glEnable(GL_BLEND); //Enable blending.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        */

        // textures
        std::unique_ptr<Image> fishSkinBlueMap = loadImage("../assets/textures/FishSkinBlue.jpg");
        GLuint blueSkin;
        glGenTextures(1, &blueSkin);
        glBindTexture(GL_TEXTURE_2D, blueSkin);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fishSkinBlueMap->getWidth(), fishSkinBlueMap->getHeight(), 0, GL_RGBA, GL_FLOAT, fishSkinBlueMap->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        std::unique_ptr<Image> fishSkinGreenMap = loadImage("../assets/textures/FishSkinGreen.jpg");
        GLuint greenSkin;
        glGenTextures(1, &greenSkin);
        glBindTexture(GL_TEXTURE_2D, greenSkin);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fishSkinGreenMap->getWidth(), fishSkinGreenMap->getHeight(), 0, GL_RGBA, GL_FLOAT, fishSkinGreenMap->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        std::unique_ptr<Image> fishSkinRedMap = loadImage("../assets/textures/FishSkinRed.jpg");
        GLuint redSkin;
        glGenTextures(1, &redSkin);
        glBindTexture(GL_TEXTURE_2D, redSkin);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fishSkinRedMap->getWidth(), fishSkinRedMap->getHeight(), 0, GL_RGBA, GL_FLOAT, fishSkinRedMap->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        std::unique_ptr<Image> fishSkinGoldenMap = loadImage("../assets/textures/FishSkinGold.jpg");
        GLuint goldenSkin;
        glGenTextures(1, &goldenSkin);
        glBindTexture(GL_TEXTURE_2D, goldenSkin);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fishSkinGoldenMap->getWidth(), fishSkinGoldenMap->getHeight(), 0, GL_RGBA, GL_FLOAT, fishSkinGoldenMap->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        std::unique_ptr<Image> waterMap = loadImage("../assets/textures/waterAlpha.png");
        GLuint water;
        glGenTextures(1, &water);
        glBindTexture(GL_TEXTURE_2D, water);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, waterMap->getWidth(), waterMap->getHeight(), 0, GL_RGBA, GL_FLOAT, waterMap->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);



        // Initialize shaderss
        FilePath applicationPath(argv[0]);
        Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                    applicationPath.dirPath() + "shaders/tex3D.fs.glsl");
        program.use();

        // Initilize Uniform Variables
        // Locations des variables uniformes des shaders
        GLint uMVPMatrixLocation=glGetUniformLocation(program.getGLId(), "uMVPMatrix");
        GLint uMVMatrixLocation=glGetUniformLocation(program.getGLId(), "uMVMatrix");
        GLint uNormalMatrixLocation=glGetUniformLocation(program.getGLId(), "uNormalMatrix");

        GLint mapLocation = glGetUniformLocation(program.getGLId(), "uTexture");

        /* 
        glm::perspective {
            fovy : angle vertical de vue
            aspect : ratio de la largeur de la fenêtre par sa hauteur
            near et far : range de vision sur l'axe de la profondeur. la distance d'affichage ??? oui
        }
        */
  
        
        /*
        GLuint vbo;
        glGenBuffers(1,&vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            Sphere sphere=Sphere(1,32,16);
            glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);   
        */


        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            std::vector<float> vertex_data;
            /*for (int i = 0; i < attrib.vertices.size(); ++i) {
                vertex_data.push_back(attrib.vertices[i]);
            }*/
            glBufferData(GL_ARRAY_BUFFER, sizeof(Geometry::Vertex) * FishMesh.getVertexCount(), FishMesh.getVertexBuffer(), GL_STATIC_DRAW);
            //glBufferData(GL_ARRAY_BUFFER, vertex_data.size()*sizeof(float), vertex_data.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        GLuint vbo2;
        glGenBuffers(2, &vbo2);
        glBindBuffer(GL_ARRAY_BUFFER, vbo2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Geometry::Vertex)*BGCube.getVertexCount(), BGCube.getVertexBuffer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);


        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * FishMesh.getIndexCount(), FishMesh.getIndexBuffer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

            const GLuint VERTEX_ATTR_POSITION=0;
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

            const GLuint VERTEX_ATTR_NORMAL=1;
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

            const GLuint VERTEX_ATTR_TEXTURE=2;
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

            glBindBuffer(GL_ARRAY_BUFFER,vbo);
                glVertexAttribPointer(VERTEX_ATTR_POSITION, 
                    3, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),0);
                glVertexAttribPointer(VERTEX_ATTR_NORMAL,
                    3, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),(void*) (sizeof(glm::vec3)));
                glVertexAttribPointer(VERTEX_ATTR_TEXTURE,
                    2, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),(void*) (2*sizeof(glm::vec3)));
            glBindBuffer(GL_ARRAY_BUFFER,0);

        glBindVertexArray(0);

        GLuint vao2;
        glGenVertexArrays(1, &vao2);
        glBindVertexArray(vao2);

            const GLuint VERTEX_ATTR_POSITION2=0;
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION2);

            const GLuint VERTEX_ATTR_NORMAL2=1;
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL2);

            const GLuint VERTEX_ATTR_TEXTURE2=2;
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE2);

            glBindBuffer(GL_ARRAY_BUFFER,vbo2);
                glVertexAttribPointer(VERTEX_ATTR_POSITION2, 
                    3, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),0);
                glVertexAttribPointer(VERTEX_ATTR_NORMAL2,
                    3, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),(void*) (sizeof(glm::vec3)));
                glVertexAttribPointer(VERTEX_ATTR_TEXTURE2,
                    2, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),(void*) (2*sizeof(glm::vec3)));
            glBindBuffer(GL_ARRAY_BUFFER,0);

        glBindVertexArray(0);

        
    /*********************************/

    // création des fishes
    std::vector<Fish> fishherd = createHerd(FISH_NUMBER);
    Fish playerFish = Fish(glm::vec3(0), glm::vec3(0, 0, -1), .2, .2, Sphere(1, 32, 16), 10000);

    // création de la caméra
    Camera camera = Camera();

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

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            } 
        }

        /*********************************/
           // RENDERING CODE

            // camera
            glm::mat4 viewMatrix = camera.getViewMatrix();

            // std::cout << viewMatrix << std::endl;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.f, 0.f, 0.3f, 1.f);

            glBindVertexArray(vao);
                // Initialize Render Matrix  
                glm::mat4 ProjMatrix = glm::perspective(glm::radians(100.f), (GLfloat)width/(GLfloat)height, 0.1f, 100.f);
                    // View angle, ratio width/height, nearest depth, furthest depth
                // glm::mat4 MVMatrix = glm::translate(glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),glm::vec4(0,0,0,1)), glm::vec3(0,0,-5));
                glm::mat4 MVMatrix = glm::lookAt(glm::vec3(0, 0, camera.getDistance()), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * viewMatrix;
                    // On voit du coté négatif des Z par défaut en OpenGL
                glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


                /*
                MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));

                // envoi des matrices au GPU.
                glUniformMatrix4fv(uMVMatrixLocation,1,GL_FALSE,glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uMVPMatrixLocation,1,GL_FALSE,glm::value_ptr(ProjMatrix*MVMatrix));
                glUniformMatrix4fv(uNormalMatrixLocation,1,GL_FALSE,glm::value_ptr(NormalMatrix));

                glBindTexture(GL_TEXTURE_2D, earth);
                    glUniform1i(mapLocation, 0);
                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                glBindTexture(GL_TEXTURE_2D, 0);

                for (size_t i = 0; i < 32; ++i) {
                    glm::mat4 MVMatrix = glm::translate(glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),glm::vec4(0,0,0,1)), glm::vec3(0,0,-5));

                    MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), axes[i]);
                    MVMatrix = glm::translate(MVMatrix, startPosition[i]);
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(.1, .1, .1));
                    MVMatrix = glm::rotate(MVMatrix, -windowManager.getTime(), axes[i]);

                    glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
                    glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));                    

                    glBindTexture(GL_TEXTURE_2D, moon);
                        glUniform1i(mapLocation, 0);
                        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
                */

                for (Fish &fish : fishherd) {

                    //glm::mat4 MVMatrix = glm::translate(glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),glm::vec4(0,0,0,1)), glm::vec3(0,0,-5));                   
                    glm::mat4 MVMatrix = glm::lookAt(glm::vec3(0, 0, camera.getDistance()), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * viewMatrix;
                    
                    MVMatrix = fish.move(MVMatrix, windowManager);
                    passTrough(fish);
                    

                    for (Fish &otherFish : fishherd) {
                        if (fish.id != otherFish.id) {
                            separation(fish, otherFish);
                            alignment(fish, otherFish);
                        }
                    }
                    cohesion(fish, fishherd);
                    separation(playerFish, fish);
                    alignment(playerFish, fish);
                    //wallSeparation(fish);
                    GLuint texture;
                    if (fish.id % 3 == 0) texture = blueSkin;
                    if (fish.id % 3 == 1) texture = greenSkin;
                    if (fish.id % 3 == 2) texture = redSkin;
                    fish.draw(MVMatrix, ProjMatrix, NormalMatrix, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, FishMesh, texture);

                    //std::cout << fish.angle() << std::endl;
                    //std::cout << fish.position() << std::endl;
                }

                MVMatrix = playerFish.move(MVMatrix, windowManager);
                passTrough(playerFish);
                playerFish.draw(MVMatrix, ProjMatrix, NormalMatrix, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, FishMesh, goldenSkin);

            glBindVertexArray(0);

            // draw cube aire de jeu
            glBindVertexArray(vao2);
                MVMatrix = glm::lookAt(glm::vec3(0, 0, camera.getDistance()), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * viewMatrix;
                MVMatrix = glm::scale(MVMatrix, glm::vec3(10.f, 10.f, 10.f));
                MVMatrix = glm::translate(MVMatrix, glm::vec3(-1.f, -1.f, -1.f));

                glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
                glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                glBindTexture(GL_TEXTURE_2D, water);
                    glDrawArrays(GL_LINES, 0, BGCube.getVertexCount());       
                    MVMatrix = glm::lookAt(glm::vec3(0, 0, camera.getDistance()), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * viewMatrix;
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(10.f, 10.f, 10.f));
                    MVMatrix = glm::rotate(MVMatrix, glm::radians(90.0f), glm::vec3(0.f, 0.f, 1.f));
                    MVMatrix = glm::translate(MVMatrix, glm::vec3(-1.f, -1.f, -1.f));     
                    glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
                    glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glDrawArrays(GL_LINES, 0, BGCube.getVertexCount());            
                glBindTexture(GL_TEXTURE_2D, 0);
            glBindVertexArray(0);


                // faudra ranger ça un peu mieux
                // on fera peut-être ça un jour
                while (windowManager.pollEvent(e)) {
                    if (e.type == SDL_QUIT) {
                        done = true;
                    } else if (e.type == SDL_KEYDOWN) {
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
                    } else if (e.type == SDL_MOUSEMOTION) {
                        camera.rotateLeft(e.motion.xrel);
                        camera.rotateUp(e.motion.yrel);
                    }
                }

                // par contre ça en vrai ça peut rester là
                if (moveUp) {
                    playerFish.turn(0, 1, 10);
                }

                if (moveDown) {
                    playerFish.turn(0, -1, 10);
                }

                if (moveLeft) {
                    playerFish.turn(2, -1, 10);
                }

                if (moveRight) {
                    playerFish.turn(2, 1, 10);
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
        /*********************************/

        // Update the display
        windowManager.swapBuffers();
    }

    /*********************************/
       // RESSOURCES RELEASE
        glDeleteBuffers(1,&vbo);
        glDeleteVertexArrays(1,&vao);
        // glDeleteTextures(1, &earth);
    /*********************************/

    return EXIT_SUCCESS;
}