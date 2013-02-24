#include "shadowSystem.h"

ShadowSystem::ShadowSystem(GLuint& depthMap, Spotlight& light){
    this->depthMap = depthMap;
    this->light = light;
    addComponentType<GeoComponent>();

    rot = 0;
    fbo = 0; // need this?
    colorTex = 0;
    shadowMap = 0;

    shadowBias = glm::mat4(
        glm::vec4(0.5f,0.0f,0.0f,0.0f),
        glm::vec4(0.0f,0.5f,0.0f,0.0f),
        glm::vec4(0.0f,0.0f,0.5f,0.0f),
        glm::vec4(0.5f,0.5f,0.5f,1.0f)
    );

    shadowShader.load("shaders/shadowVs.glsl", "shaders/shadowFs.glsl");
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    GLfloat border[]={1.0f,0.0f,0.0f,0.0f};

    int w = 800;
    int h = 600;

    // // create a RGBA color texture
    // glGenTextures(1, &colorTex);
    // glBindTexture(GL_TEXTURE_2D, colorTex);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
    //                     w, h, 
    //                     0, GL_RGBA, GL_UNSIGNED_BYTE,
    //                     NULL); 

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
    //glClear(GL_DEPTH_BUFFER_BIT);

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
    transformationMapper.init(*world);
    debugMapper.init(*world);
}

void ShadowSystem::begin(){
    // glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glUseProgram(shadowShader.program);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowMap, 0);
    // glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    GLuint vbo = geoMapper.get(e)->vbo;
    GLuint ibo = geoMapper.get(e)->ibo;
    glm::vec4 *color = debugMapper.get(e)->color;

    perspective = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

    TransformationComponent *trans = transformationMapper.get(e);
    model = trans->getModelMatrix();
    
    // model = glm::translate(glm::mat4(1.0f), *trans->pos);
    // model = glm::rotate(model, *trans->angle, *trans->axis);
    // model = glm::scale(model, *trans->scale);
    // model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    glm::mat4 inv = glm::inverse(light.viewMatrix);
    // shadowMatrix = shadowBias * perspective * inv * view * model;
    // shadowMatrix = shadowBias * perspective * light.viewMatrix * model;
    // shadowMatrix = shadowBias * perspective * view * model;
    shadowMatrix = shadowBias * light.perspectiveMatrix * (light.viewMatrix) * model;

    if(!isPaused) {
        rot = 0.5f;
    } else {
        rot = 0;
    }
    
    MV = view * model;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    printGlError();
    GLuint uMVPmatDepth = glGetUniformLocationARB(shadowShader.program, "uPMatrix");
    GLuint uMVMatrixDepth = glGetUniformLocationARB(shadowShader.program, "uMVMatrix");
    GLuint uMMatrixDepth = glGetUniformLocationARB(shadowShader.program, "uMMatrix");
    GLuint uShadowMatrix = glGetUniformLocationARB(shadowShader.program, "uShadowMatrix");
    GLuint uColor = glGetUniformLocationARB(shadowShader.program, "uColor");
    printGlError();

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    printGlError();

    glUniformMatrix4fv(uMVMatrixDepth, 1, FALSE, (const GLfloat*) glm::value_ptr(MV));
    glUniformMatrix4fv(uMMatrixDepth, 1, FALSE, (const GLfloat*) glm::value_ptr(model));
    glUniformMatrix4fv(uMVPmatDepth, 1, FALSE, (const GLfloat*) glm::value_ptr(perspective));
    glUniformMatrix4fv(uShadowMatrix, 1, FALSE, (const GLfloat*) glm::value_ptr(shadowMatrix));
    glUniform4fv(uColor, 1, (const GLfloat*) glm::value_ptr(*color));

    glBindTexture(GL_TEXTURE_2D, depthMap);
    GLint uShadowmapSampler = glGetUniformLocation(shadowShader.program, "uShadowmapSampler");
    glUniform1i(uShadowmapSampler, 0);
    
    printGlError();
    glDrawElements(GL_TRIANGLES, geoMapper.get(e)->triIndex.size(), GL_UNSIGNED_INT, 0);
    printGlError();
}