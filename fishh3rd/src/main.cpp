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
#include <glimac/fish.hpp>
#include <glimac/rock.hpp>
#include <glimac/boids.hpp>
#include <glimac/walls.hpp>
#include <glimac/assets.hpp>

//                                                         BEST VALUES
const unsigned int FISH_NUMBER = 200; //                    peu, entre 10 et 15 ça me semble pas mal ?
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

using namespace glimac;

// - - - - - - M A I N - - - - - -

int main(int argc, char** argv) {

    Geometry FishMesh;
    FishMesh.loadOBJ("../assets/models/Fish2.obj", "../assets/models/Fish2.mtl");
    //FishMesh.loadOBJ("../assets/models/FishOriented.obj", "../assets/models/FishOriented.mtl");

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

    std::vector<Geometry> rockShapes;
    rockShapes.push_back(Rock1Mesh);
    rockShapes.push_back(Rock2Mesh);
    rockShapes.push_back(Rock3Mesh);
    rockShapes.push_back(Rock4Mesh);

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
        importTexture(LeafMap, leafSkin);

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

        /*
        uniform vec3 uKd;
        uniform vec3 uKs;
        uniform float uShininess;

        uniform vec3 uLightDir_vs;
        uniform vec3 uLightIntensity;
        */

        GLint uKdLocation = glGetUniformLocation(program.getGLId(), "uKd");
        GLint uKsLocation = glGetUniformLocation(program.getGLId(), "uKs");
        GLint uShininessLocation = glGetUniformLocation(program.getGLId(), "uShininess");
        GLint uLightDir_vsLocation = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
        GLint uLightIntensityLocation = glGetUniformLocation(program.getGLId(), "uLightIntensity");

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

        GLuint vao3;
        glGenVertexArrays(1, &vao3);
        glBindVertexArray(vao3);

            const GLuint VERTEX_ATTR_POSITION3=0;
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION3);

            const GLuint VERTEX_ATTR_NORMAL3=1;
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL3);

            const GLuint VERTEX_ATTR_TEXTURE3=2;
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE3);

            glBindBuffer(GL_ARRAY_BUFFER,vao3);
                glVertexAttribPointer(VERTEX_ATTR_POSITION3, 
                    3, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),0);
                glVertexAttribPointer(VERTEX_ATTR_NORMAL3,
                    3, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),(void*) (sizeof(glm::vec3)));
                glVertexAttribPointer(VERTEX_ATTR_TEXTURE3,
                    2, GL_FLOAT, GL_FALSE, 
                    sizeof(Geometry::Vertex),(void*) (2*sizeof(glm::vec3)));
            glBindBuffer(GL_ARRAY_BUFFER,0);

        glBindVertexArray(0);

        
    /*********************************/

    // création des fishes
    std::vector<Fish> fishherd = createHerd(FISH_NUMBER, AREA, SPEED);
    Fish playerFish = Fish(glm::vec3(0), glm::vec3(0, 0, -1), .15, .4, Sphere(1, 32, 16), 10000);

    // création des décors
    std::vector<Rock> rockHerd = createRocks(rockShapes);

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
                    if (fish.id % 6 == 0) texture = blueSkin;
                    if (fish.id % 6 == 1) texture = greenSkin;
                    if (fish.id % 6 == 2) texture = redSkin;
                    if (fish.id % 6 == 3) texture = pinkSkin;
                    if (fish.id % 6 == 4) texture = cyanSkin;
                    if (fish.id % 6 == 5) texture = yellowSkin;
                    //if (fish.id % 7 == 6) texture = silverSkin;
                    fish.draw(MVMatrix, ProjMatrix, NormalMatrix, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, FishMesh, texture);

                    //std::cout << fish.angle() << std::endl;
                    //std::cout << fish.position() << std::endl;
                }

                playerFish.move(windowManager);
                passTrough(playerFish, AREA);
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

                /*
                GLint uKdLocation = glGetUniformLocation(program.getGLId(), "uKd");
                GLint uKsLocation = glGetUniformLocation(program.getGLId(), "uKs");
                GLint uShininessLocation = glGetUniformLocation(program.getGLId(), "uShininess");
                GLint uLightDir_vsLocation = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
                GLint uLightIntensityLocation = glGetUniformLocation(program.getGLId(), "uLightIntensity")
                */




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

            glBindVertexArray(vao3);

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




                    glDrawArrays(GL_TRIANGLE_FAN, 0, Rock1Mesh.getVertexCount());   
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