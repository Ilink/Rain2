#include "renderSystem.h"

RenderSystem::RenderSystem(){
    addComponentType<GeoComponent>();
    addComponentType<PhongComponent>();
}

void RenderSystem::initialize(){
    geoMapper.init(*world);
    phongMapper.init(*world);
}

void RenderSystem::processEntity(artemis::Entity &e){
    // geoMapper.get(e)->
    // VAO Setup & shader binding
    GLuint shader = phongMapper.get(e)->shader.program;
    GLuint vao = geoMapper.get(e)->vao;
    GLuint vbo = geoMapper.get(e)->vbo;
    GLuint ibo = geoMapper.get(e)->ibo;
    
    glBindAttribLocation(shader, 0, "pos");
    glBindAttribLocation(shader, 1, "uMVPmat");
    glBindAttribLocation(shader, 2, "InTexCoord0");
    glBindAttribLocation(shader, 3, "InNormal");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); // current vao

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //////////////////

    error = glGetError();
    printGlError(error);

    // cleanup here
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}