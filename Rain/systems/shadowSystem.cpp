#include "shadowSystem.h"

ShadowSystem::ShadowSystem(){
    // Artemis Setup
    addComponentType<GeoComponent>();

    rot = 0;
    fbo = 0; // need this?
    shadowMap = 0;

    glm::mat4 Model = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f));
    MVP = Model;

    // shadowShader.load("shaders/shadowVs.glsl", "shaders/shadowFs.glsl");
    depthShader.load("shaders/depthVs.glsl", "shaders/depthFs.glsl");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    GLfloat border[]={1.0f,0.0f,0.0f,0.0f};

    // Texture
    glGenTextures(1, &shadowMap);
    // glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
    glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,border); 
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_REF_TO_TEXTURE); 
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,GL_LESS);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 256, 256, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

    // FBO
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // glDrawBuffer(GL_NONE);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,shadowMap,0);

    printGlError();

    GLenum FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(FBOstatus != GL_FRAMEBUFFER_COMPLETE)
        printf("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO\n");

    // cleanup
    glBindTexture(GL_TEXTURE_2D, NULL);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);

    printGlError();
}

void ShadowSystem::initialize(){
    geoMapper.init(*world);

}

void ShadowSystem::processEntity(artemis::Entity &e){
    // glViewport(0, 0, 800, 600);
    GLuint vbo = geoMapper.get(e)->vbo;
    GLuint ibo = geoMapper.get(e)->ibo;

    rot += 0.5f;
    MV = glm::rotate(MVP, rot, glm::vec3(0.5f, 1.0f, 0.0f));

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClear(GL_DEPTH_BUFFER_BIT);

    glUseProgram(depthShader.program);
    // glBindTexture(GL_TEXTURE_2D, shadowMap);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
    glDrawBuffer(GL_NONE);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // these need to go elsewhere, it's bad to get them every frame
    //GLuint uMVPmatShadow = glGetUniformLocationARB(shadowShader.program, "uPMatrix");
    //GLuint uMVMatrixShadow = glGetUniformLocationARB(shadowShader.program, "uMVMatrix");
    //GLuint uShadowmapSampler = glGetUniformLocationARB(shadowShader.program, "uShadowmapSampler");
    GLuint uMVPmatDepth = glGetUniformLocationARB(depthShader.program, "uPMatrix");
    GLuint uMVMatrixDepth = glGetUniformLocationARB(depthShader.program, "uMVMatrix");
    printGlError();

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    printGlError();

    glUniformMatrix4fv(uMVMatrixDepth, 1, FALSE, (const GLfloat*) glm::value_ptr(MV));
    glUniformMatrix4fv(uMVPmatDepth, 1, FALSE, (const GLfloat*) glm::value_ptr(MVP));
    
    printGlError();
    // error - FBO not setup correctly
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