#include "depthSystem.h"

DepthSystem::DepthSystem(Spotlight& light){
    // Artemis Setup
    addComponentType<GeoComponent>();

    rot = 0;
    fbo = 0; // need this?
    depthMap = 0;
    colorTex = 0;
    depth = 0;

    this->light = light;

    depthShader.load("shaders/depthVs.glsl", "shaders/depthFs.glsl");
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    GLfloat border[]={1.0f,0.0f,0.0f,0.0f};

    int w = 800;
    int h = 600;
     
    // create a depth texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                        w, h, 
                        0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE,
                        NULL);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    
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

    // glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthMap, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

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

void DepthSystem::initialize(){
    geoMapper.init(*world);
    transformationMapper.init(*world);
}

void DepthSystem::begin(){
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glUseProgram(depthShader.program);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    if(toggleCull){
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DepthSystem::end(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisable(GL_CULL_FACE);
}

void DepthSystem::processEntity(artemis::Entity &e){
    // glViewport(0, 0, 800, 600);
    GLuint vbo = geoMapper.get(e)->vbo;
    GLuint ibo = geoMapper.get(e)->ibo;

    // rot += 0.5f;
    // MV = glm::rotate(shadowMVP, rot, glm::vec3(0.5f, 1.0f, 0.0f));

    // glDepthRange(0.5, 10);
    // printf("depth: %f\n", depth);
    // view = glm::rotate(view, rot, glm::vec3(0.5f, 1.0f, 0.0f));

    light.update();
    TransformationComponent *trans = transformationMapper.get(e);
    model = trans->getModelMatrix();
    // model = glm::translate(glm::mat4(1.0f), *trans->pos);
    // model = glm::rotate(model, *trans->angle, *trans->axis);
    // model = glm::scale(model, *trans->scale);
    // model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    perspective = glm::perspective(45.0f, 4.0f / 3.0f, 5.0f, 20.f);
    MV = light.viewMatrix * model;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // these need to go elsewhere, it's bad to get them every frame
    GLuint uMVPmatDepth = glGetUniformLocationARB(depthShader.program, "uPMatrix");
    GLuint uMVMatrixDepth = glGetUniformLocationARB(depthShader.program, "uMVMatrix");
    printGlError();

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    printGlError();

    glUniformMatrix4fv(uMVMatrixDepth, 1, FALSE, (const GLfloat*) glm::value_ptr(MV));
    glUniformMatrix4fv(uMVPmatDepth, 1, FALSE, (const GLfloat*) glm::value_ptr(perspective));
    
    printGlError();
    // error - FBO not setup correctly
    glDrawElements(GL_TRIANGLES, geoMapper.get(e)->triIndex.size(), GL_UNSIGNED_INT, 0);
    printGlError(); // error here    
}