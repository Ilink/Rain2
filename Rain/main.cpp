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
#include "main.h"
// #include "systems/renderSystem.h"

GLuint program;
GLint attributePos;
Shader shader;
GLenum error;

GLfloat verts[] = {
  0.5f, 0.5f, 0.0f,
  0.5f, 1.5f, 0.0f,
  0.5f, 0.75f, 0.0f,
  0.0f, 1.0f, 0.0f
};

GLuint indexes[] = {
    0, 1, 2,
    2, 1, 3
};

GLuint vao = 0;
GLuint vbo = 0;
GLuint vbo2 = 0;
GLuint vboIndexes = 0;
GLuint vboIndexes2 = 0;

using namespace std;

int initResources(){
    bool loaded = shader.load("shaders/vs.glsl", "shaders/fs.glsl");
    return 1;
}

void printGlError(GLenum error){
    fprintf(stderr, "GL Error: %s\n", glewGetErrorString(error));
}

void init(){
    attributePos = glGetAttribLocation(shader.program, "pos");
    cout << attributePos << endl;

    // VBO Setup
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, &verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glGenBuffers(1, &vboIndexes);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndexes);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLfloat), &vboIndexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // VAO Setup
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    error = glGetError();
    printGlError(error);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attributePos, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(attributePos);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndexes);
    //////////////////

    error = glGetError();
    printGlError(error);

    // cleanup here
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glClearColor(0.8, 1.0, 0.85, 1.0);
}

void onDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader.program);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndexes);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawRangeElements(GL_TRIANGLES, 0, 3, 6, GL_UNSIGNED_INT, NULL);
    // glDrawArrays(GL_TRIANGLES, 0, 3);

    // there should be cleanup here but oh well
}

void freeResources(){
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
    glDeleteProgram(program);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vbo2);
    glDeleteBuffers(1, &vboIndexes);
    glDeleteBuffers(1, &vboIndexes2);
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
    init();

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