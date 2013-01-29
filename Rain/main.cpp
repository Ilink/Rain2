#include <stdio.h>
#include <stdlib.h>
// #include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include "shader.h"
#include "Artemis-Cpp/Artemis.h"
#include "systems/renderSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "main.h"
#include "geoManager.h"
#include <string>
#include "types.h"

using namespace std;

GLuint program;
GLint attributePos;
GLint uniformMVP;
Shader shader;
GLenum error;

GLfloat verts[] = {
  -0.5f, 0.5f, 0.0f,
  -0.5f, 0.25f, 0.0f,
  0.5f, 0.35f, 0.0f,
  0.0f, 0.0f, 0.0f
};

// GLfloat verts[] = {
//     0.0f, 0.0f,  -0.4f,
//     1.0f, 0.0f,  -0.4f,
//     1.0f,  1.0f,  -0.4f,
//     0.0,  1.0f,  -0.4f
// };

GLuint indexes[] = {
    0, 1, 2,
    0, 2, 3
};

vector<GLfloat> vertsVec (verts, verts + sizeof(verts) / sizeof(verts[0]) );
vector<GLuint> indexesVec (indexes, indexes + sizeof(indexes) / sizeof(indexes[0]) );

GLuint vao = 0;
GLuint vbo = 0;
GLuint ibo = 0;

glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
glm::mat4 ViewRotateX = glm::rotate(ViewTranslate,0.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
glm::mat4 View = glm::rotate(ViewRotateX,0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 Model = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f));
glm::mat4 MVP = Projection;
// glm::mat4 MVP = glm::mat4(1.0f); // identity

int initResources(){
    bool loaded = shader.load("shaders/vs.glsl", "shaders/fs.glsl");
    return 1;
}

void init(){
    attributePos = glGetAttribLocation(shader.program, "pos");
    uniformMVP = glGetUniformLocation(shader.program, "uMVPmat");

    // VBO Setup
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, &verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLfloat), &indexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // VAO Setup
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    error = glGetError();
    printGlError(error);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attributePos, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(attributePos);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBindVertexArray(0);
    //////////////////

    error = glGetError();
    printGlError(error);

    // cleanup here
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    error = glGetError();
    printGlError(error);

    glClearColor(0.8, 1.0, 0.85, 1.0); 
}

void onDisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader.program);
    glBindVertexArray(vao);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glUniformMatrix4fv(uniformMVP, 1, FALSE, (const GLfloat*) glm::value_ptr(MVP)); 
    // glUniformMatrix4fv(uniformMVP, 1, FALSE, &MVP[0][0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawRangeElements(GL_TRIANGLES, 0, 3, 6, GL_UNSIGNED_INT, NULL);

    // error = glGetError();
    // printGlError(error);

    // cleanup
    // glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void freeResources(){
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
    glDeleteProgram(shader.program);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

int main(int argc, char* argv[]) {
    sf::Window window(sf::VideoMode(800, 600), "OpenGL");
    window.setVerticalSyncEnabled(true);

    // note this must be called before any opengl operations
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }

    GeoManager geoManager;
    artemis::World world;
    artemis::SystemManager* sm = world.getSystemManager();
    RenderSystem* renderSystem = (RenderSystem*)sm->setSystem(new RenderSystem());
    artemis::EntityManager* em = world.getEntityManager();

    sm->initializeAll();

    // player.addComponent(new MovementComponent(2,4));
    // player.addComponent(new PositionComponent(0,0));
    // player.refresh();
    // PositionComponent * comp = (PositionComponent*)player.getComponent<PositionComponent>();

    artemis::Entity &square = em->create();
    square.addComponent(geoManager.create(vertsVec, indexesVec));
    square.addComponent(new PhongComponent(shader, 0, 0));
    square.refresh();

    // initResources();
    // init();

    bool running = true;

    while (running){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                running = false;
            } else if (event.type == sf::Event::Resized){
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        world.loopStart();
        world.setDelta(0.0016f);
        renderSystem->process();
        
        // onDisplay();
        window.display();
    }

    freeResources();
    return 0;
}