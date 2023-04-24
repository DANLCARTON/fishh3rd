#define GLM_FORCE_RADIANS
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
        //void turn();
        //void draw();
};

std::vector<Fish> createHerd(const unsigned int fishNumber) {
    std::vector<Fish> fishherd;
    for (unsigned int i = 0; i < fishNumber; ++i) {
        double size = 0.1;
        glm::vec3 position = glm::vec3(glm::linearRand(-1.f/size, 1.f/size), glm::linearRand(-1.f/size, 1.f/size), glm::linearRand(-1.f/size, 1.f/size));
        // std::cout << position << std::endl;
        glm::vec3 angle = glm::vec3(glm::sphericalRand(1.f));
        double speed = 1;
        Sphere shape = Sphere(1.0f, 32, 16);
        fishherd.push_back(Fish(position, angle, speed, size, shape, i));
    }
    return fishherd;
}

glm::mat4 Fish::move(glm::mat4 MVMatrix, const SDLWindowManager &wm) {
    MVMatrix = glm::translate(MVMatrix, this->angle()*(wm.getTime()+1));
    return MVMatrix;
}

int main(int argc, char** argv) {

    // Initialize SDL and open a window
    float width  = 1280;
    float height = 720; 
    SDLWindowManager windowManager(width, height, "FISHH3RD");

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

        // textures
        std::unique_ptr<Image> earthMap = loadImage("../assets/textures/EarthMap.jpg");
        GLuint earth;
        glGenTextures(1, &earth);
        glBindTexture(GL_TEXTURE_2D, earth);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, earthMap->getWidth(), earthMap->getHeight(), 0, GL_RGBA, GL_FLOAT, earthMap->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        std::unique_ptr<Image> moonMap = loadImage("../assets/textures/MoonMap.jpg");
        GLuint moon;
        glGenTextures(1, &moon);
        glBindTexture(GL_TEXTURE_2D, moon);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, moonMap->getWidth(), moonMap->getHeight(), 0, GL_RGBA, GL_FLOAT, moonMap->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);


        // Initialize shaderss
        FilePath applicationPath(argv[0]);
        Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                    applicationPath.dirPath() + "shaders/normals.fs.glsl");
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
  
        GLuint vbo;
        glGenBuffers(1,&vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            Sphere sphere=Sphere(1,32,16);
            glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);    

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
                    sizeof(ShapeVertex),0);
                glVertexAttribPointer(VERTEX_ATTR_NORMAL,
                    3, GL_FLOAT, GL_FALSE, 
                    sizeof(ShapeVertex),(void*) (sizeof(glm::vec3)));
                glVertexAttribPointer(VERTEX_ATTR_TEXTURE,
                    2, GL_FLOAT, GL_FALSE, 
                    sizeof(ShapeVertex),(void*) (2*sizeof(glm::vec3)));
            glBindBuffer(GL_ARRAY_BUFFER,0);

        glBindVertexArray(0);

        
    /*********************************/


    // Position et axe de rotation aléatoires pour les lunes.
    std::vector<glm::vec3> axes;
    for (size_t i = 0; i < 32; ++i) {
        axes.push_back(glm::sphericalRand(1.f));
    }
    std::vector<glm::vec3> startPosition;
    for (size_t i = 0; i < 32; ++i) {
        startPosition.push_back(glm::vec3(glm::linearRand(-3.f, 3.f), glm::linearRand(-3.f, 3.f), glm::linearRand(-3.f, 3.f)));
    }

    std::vector<Fish> fishherd = createHerd(40);

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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindVertexArray(vao);
                // Initialize Render Matrix  
                glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (GLfloat)width/(GLfloat)height, 0.1f, 100.f);
                    // View angle, ratio width/height, nearest depth, furthest depth
                glm::mat4 MVMatrix = glm::translate(glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),glm::vec4(0,0,0,1))
                , glm::vec3(0,0,-5));
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
                    glm::mat4 MVMatrix = glm::translate(glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),glm::vec4(0,0,0,1)), glm::vec3(0,0,-5));

                    MVMatrix = fish.move(MVMatrix, windowManager);
                    // MVMatrix = glm::translate(MVMatrix, fish.angle());
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(fish.size(), fish.size(), fish.size()));

                    glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
                    glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));    

                    glDrawArrays(GL_TRIANGLES, 0, fish.shape().getVertexCount());
                }


            glBindVertexArray(0);
        /*********************************/

        // Update the display
        windowManager.swapBuffers();
    }

    /*********************************/
       // RESSOURCES RELEASE
        glDeleteBuffers(1,&vbo);
        glDeleteVertexArrays(1,&vao);
        glDeleteTextures(1, &earth);
    /*********************************/

    return EXIT_SUCCESS;
}