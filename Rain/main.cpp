#include <stdio.h>
#include <stdlib.h>
// #include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include "shader.h"
#include "Artemis-Cpp/Artemis.h"
#include "systems/renderSystem.h"
#include "systems/shadowSystem.h"
#include "systems/depthSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "main.h"
#include "geoManager.h"
#include <string>
#include "types.h"
#include <vector>
#include "normals.h"
#include "geoBuilder.h"
#include "entityFactory.h"
#include "compositeRenderer.h"

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

/*
    1----3
    | \  |
    |  \ |
    0----2
*/
GLuint indexes[] = {
    0, 1, 2,
    2, 1, 3
};
vector<vertex> verts2;

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

    printGlError();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attributePos, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(attributePos);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBindVertexArray(0);
    //////////////////

    printGlError();

    // cleanup here
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    printGlError();

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
    verts2.push_back(vertex());
    verts2[0].x = -0.5f;
    verts2[0].y = 0.5f;
    verts2[0].z = 0.0f;
    verts2[0].nx = 0.0f;
    verts2[0].ny = 0.0f;
    verts2[0].nz = 0.0f;
    verts2[0].u = 0.0f;
    verts2[0].v = 0.0f;

    verts2.push_back(vertex());
    verts2[1].x = -0.5f;
    verts2[1].y = 0.25f;
    verts2[1].z = 0.0f;
    verts2[1].nx = 0.0f;
    verts2[1].ny = 0.0f;
    verts2[1].nz = 0.0f;
    verts2[1].u = 0.0f;
    verts2[1].v = 0.0f;

    verts2.push_back(vertex());
    verts2[2].x = 0.5f;
    verts2[2].y = 0.35f;
    verts2[2].z = 0.0f;
    verts2[2].nx = 0.0f;
    verts2[2].ny = 0.0f;
    verts2[2].nz = 0.0f;
    verts2[2].u = 0.0f;
    verts2[2].v = 0.0f;

    verts2.push_back(vertex());
    verts2[3].x = 0.0f;
    verts2[3].y = 0.0f;
    verts2[3].z = 0.0f;
    verts2[3].nx = 0.0f;
    verts2[3].ny = 0.0f;
    verts2[3].nz = 0.0f;
    verts2[3].u = 0.0f;
    verts2[3].v = 0.0f;

    calcFaceNormals(verts2, indexesVec);

    vector<vertex> boxVerts;
    vector<GLuint> boxVertIndex;
    makeBox(1,1,-1, boxVerts, boxVertIndex);
    calcFaceNormals(boxVerts, boxVertIndex);

    vector<vertex> planeVerts;
    vector<GLuint> planeVertIndex;
    makeBox(1,1,-1, planeVerts, planeVertIndex);
    calcFaceNormals(planeVerts, planeVertIndex);

    sf::Window window(sf::VideoMode(800, 600), "OpenGL");
    window.setVerticalSyncEnabled(true);

    // note this must be called before any opengl operations
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }

    shader.load("shaders/vs.glsl", "shaders/fs.glsl");
    Shader phongShader;
    phongShader.load("shaders/phongVs.glsl", "shaders/phongFs.glsl");

    GeoManager geoManager;
    artemis::World world;
    artemis::EntityManager* em = world.getEntityManager();
    artemis::SystemManager* sm = world.getSystemManager();
    EntityFactory entityFactory(em, geoManager);
    // GeoFactory geoFactory;
    
    RenderSystem* renderSystem = (RenderSystem*)sm->setSystem(new RenderSystem());
    DepthSystem* depthSystem = (DepthSystem*)sm->setSystem(new DepthSystem());
    ShadowSystem* shadowSystem = (ShadowSystem*)sm->setSystem(new ShadowSystem(depthSystem->depthMap, depthSystem->shadowMVP));
    
    vector<GLuint> passes;
    passes.push_back(depthSystem->depthMap);
    // passes.push_back(shadowSystem->shadowMap);
    CompositeRenderer compositeRenderer(passes);
    
    sm->initializeAll();

    artemis::Entity &plane = entityFactory.makePlaneEntity();
    plane.addComponent(new PhongComponent(phongShader, 0, 0));

    artemis::Entity &square = em->create();
    square.addComponent(geoManager.create(boxVerts, boxVertIndex));
    square.addComponent(new PhongComponent(phongShader, 0, 0));

    plane.refresh();
    square.refresh();
    
    // initResources();
    // init();

    bool running = true;

    while (running){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        depthSystem->process();
        shadowSystem->process();
        // renderSystem->process();

        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // compositeRenderer.render();
        
        // onDisplay();
        window.display();
    }

    freeResources();
    return 0;
}