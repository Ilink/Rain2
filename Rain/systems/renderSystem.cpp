#include "renderSystem.h"

/*
One system per shader
Operates on:
    => specific shader
    => geometry
    => optional texture

I dont know how lighting works.
It should have a subsystem that looks at every light entity and gathers data from them.
I cant have the renderSystem itself look for light components because a renderable entity would never have one.
*/

RenderSystem::RenderSystem(){
    addComponentType<GeoComponent>();
    addComponentType<PhongComponent>();
    
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    glm::mat4 ViewRotateX = glm::rotate(ViewTranslate,90.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
    glm::mat4 View = glm::rotate(ViewRotateX,0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f));
    MVP = Model;
    // MVP = glm::mat4(1.0f); // identity

    rot = 0;

    // gl state
    glClearColor(0.8, 1.0, 0.85, 1.0);
}

void RenderSystem::initialize(){
    geoMapper.init(*world);
    phongMapper.init(*world);
}

void RenderSystem::vaoSetup(GLuint vao, GLuint vbo, GLuint ibo){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    // Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),  BUFFER_OFFSET(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void RenderSystem::processEntity(artemis::Entity &e){
    GLuint shader = phongMapper.get(e)->shader.program;
    GLuint vao = geoMapper.get(e)->vao;
    GLuint vbo = geoMapper.get(e)->vbo;
    GLuint ibo = geoMapper.get(e)->ibo;

    glm::mat3 normalMatrix(MVP);
    glm::transpose(normalMatrix);

    // these need to go elsewhere, it's bad to get them every frame
    GLuint uMVPmat = glGetUniformLocationARB(shader, "uPMatrix");
    GLuint uMVMatrix = glGetUniformLocationARB(shader, "uMVMatrix");
    GLuint uNormalMatrix = glGetUniformLocationARB(shader, "uNormalMatrix");

    if(!geoMapper.get(e)->isVaoReady){
        vaoSetup(vao, vbo, ibo);
        geoMapper.get(e)->isVaoReady = true;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    rot += 0.5f;
    MV = glm::rotate(MVP, rot, glm::vec3(0.5f, 1.0f, 0.0f));

    glUniformMatrix3fv(uNormalMatrix, 1, false, (const GLfloat*) glm::value_ptr(normalMatrix));
    glUniformMatrix4fv(uMVMatrix, 1, FALSE, (const GLfloat*) glm::value_ptr(MV));
    glUniformMatrix4fv(uMVPmat, 1, FALSE, (const GLfloat*) glm::value_ptr(MVP));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //error = glGetError();
    //printGlError(error);

    // cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}