#include "shadowSystem.h"

ShadowSystem::ShadowSystem(GLuint& depthMap, glm::mat4 shadowMatrix){
    this->depthMap = depthMap;
    // Artemis Setup
    addComponentType<GeoComponent>();

    rot = 0;
    fbo = 0; // need this?
    colorTex = 0;
    shadowMap = 0;

    perspective = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    shadowView = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -10.0f));

    shadowBias = glm::mat4(
        glm::vec4(0.5f,0.0f,0.0f,0.0f),
        glm::vec4(0.0f,0.5f,0.0f,0.0f),
        glm::vec4(0.0f,0.0f,0.5f,0.0f),
        glm::vec4(0.5f,0.5f,0.5f,1.0f)
    );

    lightPerspective = shadowBias * perspective * shadowView;

    shadowShader.load("shaders/shadowVs.glsl", "shaders/shadowFs.glsl");
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    GLfloat border[]={1.0f,0.0f,0.0f,0.0f};

    int w = 800;
    int h = 600;

    // shadowmap setup
    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
                        w, h, 
                        0, GL_RGBA, GL_UNSIGNED_BYTE,
                        NULL);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
    // glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,border); 
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_REF_TO_TEXTURE); // this doesnt let us view the texture, so it is disabled for now
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,GL_LESS);

    printGlError();

    // FBO
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    printGlError();

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowMap, 0);

    GLenum FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(FBOstatus != GL_FRAMEBUFFER_COMPLETE)
        printf("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO\n");
    else
        printf("FBO ready!\n");

    // cleanup
    glBindTexture(GL_TEXTURE_2D, NULL);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //glDisableVertexAttribArray(0);

    printGlError();
}

void ShadowSystem::initialize(){
    geoMapper.init(*world);

}

void ShadowSystem::begin(){
    // glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glUseProgram(shadowShader.program);
    // glBindTexture(GL_TEXTURE_2D, depthMap);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowMap, 0);
    // glClear(GL_DEPTH_BUFFER_BIT);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    printGlError();
}

void ShadowSystem::end(){
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glDisableVertexAttribArray(0);
}

void ShadowSystem::processEntity(artemis::Entity &e){
    // glViewport(0, 0, 800, 600);
    GLuint vbo = geoMapper.get(e)->vbo;
    GLuint ibo = geoMapper.get(e)->ibo;

    rot += 0.5f;
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.5f, 1.0f, 0.0f));
    MV = view * rotate;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // these need to go elsewhere, it's bad to get them every frame
    //GLuint uMVPmatShadow = glGetUniformLocationARB(shadowShader.program, "uPMatrix");
    //GLuint uMVMatrixShadow = glGetUniformLocationARB(shadowShader.program, "uMVMatrix");
    //GLuint udepthMapSampler = glGetUniformLocationARB(shadowShader.program, "udepthMapSampler");
    printGlError();
    GLuint uPMatrix = glGetUniformLocationARB(shadowShader.program, "uPMatrix");
    GLuint uMVMatrix = glGetUniformLocationARB(shadowShader.program, "uMVMatrix");
    GLuint uShadowMatrix = glGetUniformLocationARB(shadowShader.program, "uShadowMatrix");
    printGlError();

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    printGlError();

    glUniformMatrix4fv(uPMatrix, 1, FALSE, (const GLfloat*) glm::value_ptr(perspective));
    glUniformMatrix4fv(uMVMatrix, 1, FALSE, (const GLfloat*) glm::value_ptr(MV));
    glUniformMatrix4fv(uShadowMatrix, 1, FALSE, (const GLfloat*) glm::value_ptr(lightPersp));

    glBindTexture(GL_TEXTURE_2D, depthMap);
    GLint uShadowmapSampler = glGetUniformLocation(shadowShader.program, "uShadowmapSampler");
    glUniform1i(uShadowmapSampler, 0);
    
    printGlError();
    glDrawElements(GL_TRIANGLES, geoMapper.get(e)->triIndex.size(), GL_UNSIGNED_INT, 0);
    printGlError();
}