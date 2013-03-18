#include "GBufferSystem.h"

GBufferSystem::GBufferSystem(Camera& cam): camera(cam){
    // Artemis Setup
    addComponentType<GeoComponent>();
    // addComponentType<TransformationComponent>();

    // init gl junk
    gBuffer.color = 1;
    gBuffer.normals = 0;
    gBuffer.depth = 0;
    gBuffer.spec = 0;
    fbo = 0;

    shader.load("shaders/depthVs.glsl", "shaders/depthFs.glsl");
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // this->camera = camera;
    perspective = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.f);

    uMVPmat = glGetUniformLocationARB(shader.program, "uPMatrix");
    uMVMatrix = glGetUniformLocationARB(shader.program, "uMVMatrix");
    uVMatrix = glGetUniformLocationARB(shader.program, "uVMatrix");
    uNormalMatrix = glGetUniformLocationARB(shader.program, "uNormalMatrix");

    //todo: make thse not hardcoded - they should be in the camera, or something
    int w = 800;
    int h = 600;

    // init render texture targets
    glGenTextures(1, &gBuffer.color);
    glBindTexture(GL_TEXTURE_2D, gBuffer.color);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
                        w, h, 
                        0, GL_RGBA, GL_UNSIGNED_BYTE,
                        NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &gBuffer.normals);
    glBindTexture(GL_TEXTURE_2D, gBuffer.normals);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
                        w, h, 
                        0, GL_RGB, GL_UNSIGNED_BYTE,
                        NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &gBuffer.depth);
    glBindTexture(GL_TEXTURE_2D, gBuffer.depth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                        w, h, 
                        0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE,
                        NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
    // glActiveTexture(GL_TEXTURE1);

    printGlError();

    // fbo setup
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gBuffer.color, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gBuffer.normals, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, gBuffer.depth, 0);

    printFboErrors("gbuffer");

    // Cleanup
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBufferSystem::initialize(){
    geoMapper.init(*world);
    transMapper.init(*world);
}

void GBufferSystem::begin(){
    glUseProgram(shader.program);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GBufferSystem::end(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBufferSystem::processEntity(artemis::Entity &e){
    GLuint vbo = geoMapper.get(e)->vbo;
    GLuint ibo = geoMapper.get(e)->ibo;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    // Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),  BUFFER_OFFSET(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    model = transMapper.get(e)->getModelMatrix();

    MV = camera.viewMatrix * model;
    glm::mat3 normalMatrix(MV);
    glm::transpose(normalMatrix);

    glUniformMatrix3fv(uNormalMatrix, 1, false, (const GLfloat*) glm::value_ptr(normalMatrix));
    glUniformMatrix4fv(uMVMatrix, 1, FALSE, (const GLfloat*) glm::value_ptr(MV));
    glUniformMatrix4fv(uMVPmat, 1, FALSE, (const GLfloat*) glm::value_ptr(perspective));

    printGlError();
    GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, buffers);

    glDrawElements(GL_TRIANGLES, geoMapper.get(e)->triIndex.size(), GL_UNSIGNED_INT, 0);
}