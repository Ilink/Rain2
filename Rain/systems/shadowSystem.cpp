#include "shadowSystem.h"

ShadowSystem::ShadowSystem(){
    // Artemis Setup
    addComponentType<GeoComponent>();

    glm::mat4 Model = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f));
    MVP = Model;

    // shadowShader.load("shaders/shadowVs.glsl", "shaders/shadowFs.glsl");
    depthShader.load("shaders/depthVs.glsl", "shaders/depthFs.glsl");

    GLfloat border[]={1.0f,0.0f,0.0f,0.0f};

    // Texture
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
    // fbo = 0; // need this?
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
    // glViewport(0, 0, 800, 600);
    GLuint vbo = geoMapper.get(e)->vbo;
    GLuint ibo = geoMapper.get(e)->ibo;

    // these need to go elsewhere, it's bad to get them every frame
    //GLuint uMVPmatShadow = glGetUniformLocationARB(shadowShader.program, "uPMatrix");
    //GLuint uMVMatrixShadow = glGetUniformLocationARB(shadowShader.program, "uMVMatrix");
    GLuint uMVPmatDepth = glGetUniformLocationARB(depthShader.program, "uPMatrix");
    GLuint uMVMatrixDepth = glGetUniformLocationARB(depthShader.program, "uMVMatrix");
    //GLuint uShadowmapSampler = glGetUniformLocationARB(shadowShader.program, "uShadowmapSampler");
    printGlError();

    glUseProgram(depthShader.program);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    printGlError();

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    rot += 0.5f;
    MV = glm::rotate(MVP, rot, glm::vec3(0.5f, 1.0f, 0.0f));

    glUniformMatrix4fv(uMVMatrixDepth, 1, FALSE, (const GLfloat*) glm::value_ptr(MV));
    glUniformMatrix4fv(uMVPmatDepth, 1, FALSE, (const GLfloat*) glm::value_ptr(MVP));
    
    printGlError();
    // i think there's something not being transmitted to teh shader!
    glDrawElements(GL_TRIANGLES, geoMapper.get(e)->triIndex.size(), GL_UNSIGNED_INT, 0);
    printGlError(); // error here

    // cleanup
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glDisableVertexAttribArray(0);
}    