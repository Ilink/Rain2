#include "shadowSystem.h"

ShadowSystem::ShadowSystem(GLuint& _shadowMap){
    shader.load("shaders/shadowVs.glsl", "shaders/shadowFs.glsl");

    GLfloat border[]={1.0f,0.0f,0.0f,0.0f};

    // Texture
    shadowMap = _shadowMap;
    glGenTextures(1, &shadowMap);

    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 800, 600, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
    glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,border); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_REF_TO_TEXTURE); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,GL_LESS);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, shadowMap);

    // FBO
    fbo = 0;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo); 
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,shadowMap,0);
    GLenum drawBuffers[]={GL_NONE}; // we dont want color, only depth
    glDrawBuffers(1,drawBuffers);

    // cleanup
    glBindTexture(GL_TEXTURE_2D, NULL);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    printGlError();
}

void ShadowSystem::initialize(){
    geoMapper.init(*world);

}

void ShadowSystem::processEntity(artemis::Entity &e){

    //glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //// Position
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
    //glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //glBindVertexArray(0);




    // GLuint shader = phongMapper.get(e)->shader.program;
    // // GLuint vao = geoMapper.get(e)->vao;
    // GLuint vbo = geoMapper.get(e)->vbo;
    // GLuint ibo = geoMapper.get(e)->ibo;

    // // these need to go elsewhere, it's bad to get them every frame
    // GLuint uMVPmat = glGetUniformLocationARB(shader, "uPMatrix");
    // GLuint uMVMatrix = glGetUniformLocationARB(shader, "uMVMatrix");

    // // if(!geoMapper.get(e)->isVaoReady){
    // //     vaoSetup(vao, vbo, ibo);
    // //     geoMapper.get(e)->isVaoReady = true;
    // // }

    // glClear(GL_COLOR_BUFFER_BIT);

    // glUseProgram(shader);
    // glBindVertexArray(vao);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // rot += 0.5f;
    // MV = glm::rotate(MVP, rot, glm::vec3(0.5f, 1.0f, 0.0f));

    // glUniformMatrix4fv(uMVMatrix, 1, FALSE, (const GLfloat*) glm::value_ptr(MV));
    // glUniformMatrix4fv(uMVPmat, 1, FALSE, (const GLfloat*) glm::value_ptr(MVP));

    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // printGlError();

    // // cleanup
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    // glUseProgram(0);
}    