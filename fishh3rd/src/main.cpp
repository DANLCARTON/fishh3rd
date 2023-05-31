#define GLM_FORCE_RADIANS
#define TINYOBJLOADER_IMPLEMENTATION
//#include "../glimac/src/tiny_obj_loader.h"
#include "glm/detail/type_mat.hpp"
#include <stdexcept>
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
#include <glimac/fish.hpp>
#include <glimac/rock.hpp>
#include <glimac/boids.hpp>
#include <glimac/walls.hpp>
#include <glimac/assets.hpp>
#include <glimac/VAO_VBO.hpp>
#include <glimac/inputs.hpp>

//                                                         BEST VALUES
const unsigned int FISH_NUMBER = 150; //                    200
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
const GLenum DRAW_MODE = GL_TRIANGLE_FAN; //               LOD : GL_TRIANGLE_FAN - GL_LINES_STRIP

using namespace glimac;

// - - - - - - M A I N - - - - - -

int main(int argc, char** argv) {

    Geometry FishMesh;
    FishMesh.loadOBJ("../assets/models/Fish2.obj", "../assets/models/Fish2.mtl");

    Geometry BGCube;
    BGCube.loadOBJ("../assets/models/cube.obj", "../assets/models/cube.mtl");

    Geometry LeafMesh;
    LeafMesh.loadOBJ("../assets/models/Leaf.obj", "../assets/models/Leaf.mtl");

    Geometry Rock1Mesh;
    Rock1Mesh.loadOBJ("../assets/models/Rock1.obj", "../assets/models/Rock1.mtl");

    Geometry Rock2Mesh;
    Rock2Mesh.loadOBJ("../assets/models/Rock2.obj", "../assets/models/Rock2.mtl");

    Geometry Rock3Mesh;
    Rock3Mesh.loadOBJ("../assets/models/Rock3.obj", "../assets/models/Rock3.mtl");

    Geometry Rock4Mesh;
    Rock4Mesh.loadOBJ("../assets/models/Rock4.obj", "../assets/models/Rock4.mtl");

    Geometry MiniRockMesh;
    MiniRockMesh.loadOBJ("../assets/models/MiniRock.obj", "../assets/models/MiniRock.mtl");

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
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // textures
        std::unique_ptr<Image> fishSkinBlueMap = loadImage("../assets/textures/Blue.jpg");
        GLuint blueSkin;
        importTexture(fishSkinBlueMap, blueSkin);

        std::unique_ptr<Image> fishSkinGreenMap = loadImage("../assets/textures/Green.jpg");
        GLuint greenSkin;
        importTexture(fishSkinGreenMap, greenSkin);

        std::unique_ptr<Image> fishSkinRedMap = loadImage("../assets/textures/Red.jpg");
        GLuint redSkin;
        importTexture(fishSkinRedMap, redSkin);

        std::unique_ptr<Image> fishSkinPinkMap = loadImage("../assets/textures/Pink.jpg");
        GLuint pinkSkin;
        importTexture(fishSkinPinkMap, pinkSkin);

        std::unique_ptr<Image> fishSkinCyanMap = loadImage("../assets/textures/Cyan.jpg");
        GLuint cyanSkin;
        importTexture(fishSkinCyanMap, cyanSkin);

        std::unique_ptr<Image> fishSkinYellowMap = loadImage("../assets/textures/Yellow.jpg");
        GLuint yellowSkin;
        importTexture(fishSkinYellowMap, yellowSkin);

        std::unique_ptr<Image> fishSkinSilverMap = loadImage("../assets/textures/Silver.jpg");
        GLuint silverSkin;
        importTexture(fishSkinSilverMap, silverSkin);

        std::unique_ptr<Image> fishSkinGoldenMap = loadImage("../assets/textures/Gold.jpg");
        GLuint goldenSkin;
        importTexture(fishSkinGoldenMap, goldenSkin);

        std::unique_ptr<Image> waterMap = loadImage("../assets/textures/waterAlpha.png");
        GLuint water;
        importTexture(waterMap, water);

        std::unique_ptr<Image> leafMap = loadImage("../assets/textures/Leaf.jpg");
        GLuint leafSkin;
        importTexture(leafMap, leafSkin);

        std::unique_ptr<Image> rockMap = loadImage("../assets/textures/Rock.jpg");
        GLuint rockSkin;
        importTexture(rockMap, rockSkin);

        std::unique_ptr<Image> miniRock1Map = loadImage("../assets/textures/MiniRock1.jpg");
        GLuint miniRock1Skin;
        importTexture(miniRock1Map, miniRock1Skin);

        std::unique_ptr<Image> miniRock2Map = loadImage("../assets/textures/MiniRock2.jpg");
        GLuint miniRock2Skin;
        importTexture(miniRock2Map, miniRock2Skin);

        std::unique_ptr<Image> miniRock3Map = loadImage("../assets/textures/MiniRock3.jpg");
        GLuint miniRock3Skin;
        importTexture(miniRock3Map, miniRock3Skin);

        std::unique_ptr<Image> woodMap = loadImage("../assets/textures/Wood.jpg");
        GLuint woodSkin;
        importTexture(woodMap, woodSkin);

        

        // Initialize shaderss
        FilePath applicationPath(argv[0]);
        Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                    applicationPath.dirPath() + "shaders/tex3D.fs.glsl");
                                    //applicationPath.dirPath() + "shaders/directionallight.fs.glsl");
        program.use();

        // Initilize Uniform Variables
        // Locations des variables uniformes des shaders
        GLint uMVPMatrixLocation=glGetUniformLocation(program.getGLId(), "uMVPMatrix");
        GLint uMVMatrixLocation=glGetUniformLocation(program.getGLId(), "uMVMatrix");
        GLint uNormalMatrixLocation=glGetUniformLocation(program.getGLId(), "uNormalMatrix");

        GLint mapLocation = glGetUniformLocation(program.getGLId(), "uTexture");

        GLint uKdLocation = glGetUniformLocation(program.getGLId(), "uKd");
        GLint uKsLocation = glGetUniformLocation(program.getGLId(), "uKs");
        GLint uShininessLocation = glGetUniformLocation(program.getGLId(), "uShininess");
        GLint uLightDir_vsLocation = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
        GLint uLightIntensityLocation = glGetUniformLocation(program.getGLId(), "uLightIntensity");



        GLuint vbo; // Poissons
        createVBO(vbo, FishMesh);

        GLuint vao;
        createVAO(vao, vbo);



        GLuint vbo2; // Bordures
        createVBO(vbo2, BGCube);
        
        GLuint vao2;
        createVAO(vao2, vbo2);



        GLuint vbo3_1; // Roches
        createVBO(vbo3_1, Rock1Mesh);

        GLuint vao3_1;
        createVAO(vao3_1, vbo3_1);

        GLuint vbo3_2; 
        createVBO(vbo3_2, Rock2Mesh);

        GLuint vao3_2;
        createVAO(vao3_2, vbo3_2);

        GLuint vbo3_3; 
        createVBO(vbo3_3, Rock3Mesh);

        GLuint vao3_3;
        createVAO(vao3_3, vbo3_3);

        GLuint vbo3_4; 
        createVBO(vbo3_4, Rock4Mesh);

        GLuint vao3_4;
        createVAO(vao3_4, vbo3_4);



        GLuint ibo4; // Table
        createIBO(ibo4, BGCube);

        GLuint vao4;
        createVAOfromIBO(vao4, ibo4);

        
    /*********************************/

    // création des fishes
    std::vector<Fish> fishherd = createHerd(FISH_NUMBER, AREA, SPEED);
    Fish playerFish = Fish(glm::vec3(0), glm::vec3(0, 0, -1), .15, .4, Sphere(1, 32, 16), 10000);

    // création des décors
    std::vector<Rock> rockHerd;
    rockHerd.push_back(Rock(glm::vec3(6.f, -9.f, 6.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), Rock1Mesh, vao3_1));
    rockHerd.push_back(Rock(glm::vec3(2.f, -9.f, -7.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.5f, 1.5f, 1.5f), Rock2Mesh, vao3_2));
    rockHerd.push_back(Rock(glm::vec3(8.f, -9.f, -4.1f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.5f, 1.5f, 1.5f), Rock3Mesh, vao3_3));
    rockHerd.push_back(Rock(glm::vec3(6.f, -9.f, -6.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(2.f, 2.5f, 2.f), Rock4Mesh, vao3_4));

    // création de la caméra
    Camera camera = Camera();

    glm::mat4 vm2 = camera.getViewMatrix();

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
                glm::mat4 ProjMatrix = glm::perspective(glm::radians(90.f), (GLfloat)width/(GLfloat)height, 0.1f, 100.f);
                    // View angle, ratio width/height, nearest depth, furthest depth
                // glm::mat4 MVMatrix = glm::translate(glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),glm::vec4(0,0,0,1)), glm::vec3(0,0,-5));
                
                glm::mat4 MVMatrix = glm::lookAt(glm::vec3(0, 0, camera.getDistance()), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * viewMatrix;
                    // On voit du coté négatif des Z par défaut en OpenGL
                glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

                glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
                glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                glUniform3fv(uKdLocation, 1, glm::value_ptr(glm::vec3(1.f, 0.5f, 0.2f)));
                glUniform3fv(uKsLocation, 1, glm::value_ptr(glm::vec3(1.f, 0.5f, 0.2f)));
                glUniform1f(uShininessLocation, 1.f);
                glUniform3fv(uLightDir_vsLocation, 1, glm::value_ptr(glm::vec4(0.f, -1.f, 0.f, 1.f)*viewMatrix));
                glUniform3fv(uLightIntensityLocation, 1, glm::value_ptr(glm::vec3(1.f, 1.f, 1.f)));

                for (Fish &fish : fishherd) {

                    //glm::mat4 MVMatrix = glm::translate(glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),glm::vec4(0,0,0,1)), glm::vec3(0,0,-5));                   
                    glm::mat4 MVMatrix = glm::lookAt(glm::vec3(0, 0, camera.getDistance()), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * viewMatrix;
                    
                    fish.move(windowManager);
                    passTrough(fish, AREA);
                    

                    for (Fish &otherFish : fishherd) {
                        if (fish.id != otherFish.id) {
                            separation(fish, otherFish, SEPARATION_RADIUS, SEPARATION_STRENGTH, TURN_FACTOR);
                            alignment(fish, otherFish, SEPARATION_RADIUS, ALIGNMENT_RADIUS, ALIGNMENT_STRENGTH, TURN_FACTOR);
                        }
                    }
                    cohesion(fish, fishherd, COHESION_RADIUS, COHESION_STRENGTH, TURN_FACTOR);
                    separation(playerFish, fish, SEPARATION_RADIUS, SEPARATION_STRENGTH, TURN_FACTOR);
                    alignment(playerFish, fish, SEPARATION_RADIUS, ALIGNMENT_RADIUS, ALIGNMENT_STRENGTH, TURN_FACTOR);
                    //wallSeparation(fish, AREA, WALLS_RADIUS, WALLS_STRENGTH, TURN_FACTOR);
                    GLuint texture;
                    if (fish.id % 7 == 0) texture = blueSkin;
                    if (fish.id % 7 == 1) texture = greenSkin;
                    if (fish.id % 7 == 2) texture = redSkin;
                    if (fish.id % 7 == 3) texture = pinkSkin;
                    if (fish.id % 7 == 4) texture = cyanSkin;
                    if (fish.id % 7 == 5) texture = yellowSkin;
                    if (fish.id % 7 == 6) texture = silverSkin;
                    fish.draw(MVMatrix, ProjMatrix, NormalMatrix, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, FishMesh, texture, DRAW_MODE);

                    //std::cout << fish.angle() << std::endl;
                    //std::cout << fish.position() << std::endl;
                }

                playerFish.move(windowManager);
                passTrough(playerFish, AREA);
                playerFish.draw(MVMatrix, ProjMatrix, NormalMatrix, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, FishMesh, goldenSkin, DRAW_MODE);

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

            // DECOR

            glBindVertexArray(vao4); // Table
                MVMatrix = glm::lookAt(glm::vec3(0, 0, camera.getDistance()), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * viewMatrix;
                MVMatrix = glm::scale(MVMatrix, glm::vec3(20.f, 1.f, 20.f));
                MVMatrix = glm::rotate(MVMatrix, glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f));
                MVMatrix = glm::translate(MVMatrix, glm::vec3(-1.f, 10.f, -1.f));

                glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
                glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo4);
                glBindTexture(GL_TEXTURE_2D, woodSkin);
                    glDrawElements(GL_TRIANGLES, (unsigned int)36, GL_UNSIGNED_INT, 0);
                glBindTexture(GL_TEXTURE_2D, 0);
            glBindVertexArray(0);

            

            glBindVertexArray(vao3_1);

                MVMatrix = glm::lookAt(glm::vec3(0, 0, camera.getDistance()), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * viewMatrix;

                glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
                glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                glUniform3fv(uKdLocation, 1, glm::value_ptr(glm::vec3(1.f, 0.5f, 0.2f)));
                glUniform3fv(uKsLocation, 1, glm::value_ptr(glm::vec3(1.f, 0.5f, 0.2f)));
                glUniform1f(uShininessLocation, 1.f);
                glUniform3fv(uLightDir_vsLocation, 1, glm::value_ptr(glm::vec4(0.f, -1.f, 0.f, 1.f)*viewMatrix));
                glUniform3fv(uLightIntensityLocation, 1, glm::value_ptr(glm::vec3(1.f, 1.f, 1.f)));

                for (Rock &rock : rockHerd) {
                    rock.draw(MVMatrix, ProjMatrix, NormalMatrix, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, rock.m_shape, rockSkin);
                }
            glBindVertexArray(0);

            for (Rock &rock : rockHerd) {
                glBindVertexArray(rock.m_vao);

                MVMatrix = glm::lookAt(glm::vec3(0, 0, camera.getDistance()), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * viewMatrix;

                glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
                glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                glUniform3fv(uKdLocation, 1, glm::value_ptr(glm::vec3(1.f, 0.5f, 0.2f)));
                glUniform3fv(uKsLocation, 1, glm::value_ptr(glm::vec3(1.f, 0.5f, 0.2f)));
                glUniform1f(uShininessLocation, 1.f);
                glUniform3fv(uLightDir_vsLocation, 1, glm::value_ptr(glm::vec4(0.f, -1.f, 0.f, 1.f)*viewMatrix));
                glUniform3fv(uLightIntensityLocation, 1, glm::value_ptr(glm::vec3(1.f, 1.f, 1.f)));

                rock.draw(MVMatrix, ProjMatrix, NormalMatrix, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, rock.m_shape, rockSkin);
            glBindVertexArray(0);
            }

        if (e.type != SDL_QUIT) {
            SDLinputs(windowManager, TURN_FACTOR, camera, playerFish, e);
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