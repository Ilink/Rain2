#include <stdio.h>
#include <stdlib.h>
// #include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include "shader.h"
#include <Artemis-Cpp/Artemis.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "systems/renderSystem.h"

GLuint program;
GLint attribute_coord2d;
Shader shader;

using namespace std;

int initResources(){
    bool loaded = shader.load("shaders/vs.glsl", "shaders/fs.glsl");
    return 1;
}

void onDisplay(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // glUseProgram(program);
    glUseProgram(shader.program);
    glEnableVertexAttribArray(attribute_coord2d);

    GLfloat verts[] = {
      0.0f, 0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f
    };

    glVertexAttribPointer(attribute_coord2d,3,GL_FLOAT,GL_FALSE,0,verts);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(attribute_coord2d);
}

void freeResources(){
    glDeleteProgram(program);
}


int main(int argc, char* argv[]) {
    sf::Window window(sf::VideoMode(800, 600), "OpenGL");
    window.setVerticalSyncEnabled(true);

    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }

    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 ViewRotateX = glm::rotate(ViewTranslate,0.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
    glm::mat4 View = glm::rotate(ViewRotateX,0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f));
    glm::mat4 MVP = Projection * View * Model;

    // shader.setParameter("uMVPmat",  (const float*) glm::value_ptr(MVP));

    initResources();

    bool running = true;
    while (running){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                running = false;
            } else if (event.type == sf::Event::Resized){
                glViewport(0, 0, event.size.width, event.size.height);
            }
            onDisplay();
            window.display();
        }
    }

    freeResources();
    return 0;
}