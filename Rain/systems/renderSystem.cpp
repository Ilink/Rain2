#include "renderSystem.h"

/*
One system per shader CATEGORY!
a category is a set of inputs. A lot of shaders, that arent special purpose
should follow the typical set laid out here. 

I think other shaders will mostly feed into the composite system

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
    
    perspective = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    model = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f));

    glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    glm::mat4 ViewRotateX = glm::rotate(ViewTranslate,90.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
    glm::mat4 View = glm::rotate(ViewRotateX,0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    rot = 0;

    // gl state
    glClearColor(0.8, 1.0, 0.85, 1.0);
}

void RenderSystem::initialize(){
    geoMapper.init(*world);
    phongMapper.init(*world);
}

void RenderSystem::vaoSetup(GLuint vao, GLuint vbo, GLuint ibo){
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    // Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),  BUFFER_OFFSET(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void RenderSystem::processEntity(artemis::Entity &e){
    // printf("renderable entity\n");
    GLuint shader = phongMapper.get(e)->shader->program; //todo: this only needs to be bound once!
                                                        //could be: startup => process => teardown
    GLuint vao = geoMapper.get(e)->vao;
    GLuint vbo = geoMapper.get(e)->vbo;
    GLuint ibo = geoMapper.get(e)->ibo;

    // these need to go elsewhere, it's bad to get them every frame
    GLuint uMVPmat = glGetUniformLocationARB(shader, "uPMatrix");
    GLuint uMVMatrix = glGetUniformLocationARB(shader, "uMVMatrix");
    GLuint uNormalMatrix = glGetUniformLocationARB(shader, "uNormalMatrix");

    if(!geoMapper.get(e)->isVaoReady){
        vaoSetup(vao, vbo, ibo);
        printf("vao: %i\n", vao);
        geoMapper.get(e)->isVaoReady = true;
    }

    glUseProgram(shader);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    rot = 0.5f;
    view = glm::rotate(view, rot, glm::vec3(0.5f, 1.0f, 0.0f));

    MV = view * model;
    glm::mat3 normalMatrix(MV);
    glm::transpose(normalMatrix);

    glUniformMatrix3fv(uNormalMatrix, 1, false, (const GLfloat*) glm::value_ptr(normalMatrix));
    glUniformMatrix4fv(uMVMatrix, 1, FALSE, (const GLfloat*) glm::value_ptr(MV));
    glUniformMatrix4fv(uMVPmat, 1, FALSE, (const GLfloat*) glm::value_ptr(perspective));

    glDrawElements(GL_TRIANGLES, geoMapper.get(e)->triIndex.size(), GL_UNSIGNED_INT, 0);

    //error = glGetError();
    //printGlError(error);

    // cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}