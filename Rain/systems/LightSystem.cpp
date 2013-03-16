#include "LightSystem.h"

LightSystem::LightSystem(Camera& camera, GBuffer& gBuffer)
    :camera(camera),
    gBuffer(gBuffer)
{
    /////////////////////////////
    // Artemis Setup
    /////////////////////////////
    addComponentType<GeoComponent>();
    addComponentType<LightComponent>();
    addComponentType<TransformationComponent>();

    lightShader.load("shaders/lightVs.glsl", "shaders/lightFs.glsl");

    vector<vertex> planeVerts;
    vector<GLuint> planeVertIndex;
    makePlane(2,2, planeVerts, planeVertIndex);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)*planeVerts.size(), &planeVerts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*planeVertIndex.size(), &planeVertIndex[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    uMVPmat = glGetUniformLocation(lightShader.program, "uPMatrix");
    uMVMatrix = glGetUniformLocation(lightShader.program, "uMVMatrix");
    uNormalsSampler = glGetUniformLocation(lightShader.program, "uNormalsSampler");
    uColorSampler = glGetUniformLocation(lightShader.program, "uColorSampler");
    uLightPosition = glGetUniformLocation(lightShader.program, "uLightPosition");
    uLightDirection = glGetUniformLocation(lightShader.program, "uLightDirection");

    perspective = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.f);
}

void LightSystem::initialize(){
    lightMapper.init(*world);
    geoMapper.init(*world);
    transMapper.init(*world);
}

void LightSystem::begin(){
    glUseProgram(lightShader.program);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LightSystem::processEntity(artemis::Entity &e){
    // printf("processing light entity\n");
    // GLuint vbo = geoMapper.get(e)->vbo;
    // GLuint ibo = geoMapper.get(e)->ibo;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));

    // Tex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(24));

    model = transMapper.get(e)->getModelMatrix();

    MV = camera.viewMatrix * model;
    glUniformMatrix4fv(uMVMatrix, 1, FALSE, (const GLfloat*) glm::value_ptr(MV));
    glUniformMatrix4fv(uMVPmat, 1, FALSE, (const GLfloat*) glm::value_ptr(perspective));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gBuffer.color);
    glUniform1i(uColorSampler, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gBuffer.normals);
    glUniform1i(uNormalsSampler, 1);

    // need depth

    printGlError();

    glDrawElements(GL_TRIANGLES, geoMapper.get(e)->triIndex.size(), GL_UNSIGNED_INT, 0);
}

void LightSystem::end(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}