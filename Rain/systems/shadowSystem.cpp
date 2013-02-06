#include "shadowSystem.h"

ShadowSystem::ShadowSystem(GLuint& _shadowMap){
    GLfloat border[]={1.0f,0.0f,0.0f,0.0f};

    shadowMap = _shadowMap;
    glGenTextures(1, &shadowMap);

    fbo = 0;
    glGenFramebuffers(1, &fbo);
    // glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

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

    glBindFramebuffer(GL_FRAMEBUFFER, fbo); 
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,shadowMap,0);
    GLenum drawBuffers[]={GL_NONE}; // we dont want color, only depth
    glDrawBuffers(1,drawBuffers);

    // cleanup
    glBindTexture(GL_TEXTURE_2D, NULL);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // error = glGetError();
    printGlError();
    // GLenum error = glewInit();
    // if (error != GLEW_OK) {
    //     fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
    //     return 1;
    // }
}

void ShadowSystem::initialize(){
    geoMapper.init(*world);
}

void ShadowSystem::processEntity(artemis::Entity &e){     


}    