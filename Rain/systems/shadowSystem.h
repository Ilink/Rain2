#ifndef SHADOWSYSTEM_H
#define SHADOWSYSTEM_H

#include "../Artemis-Cpp/Artemis.h"
#include "../components/geoComponent.h"
#include "../components/phongComponent.h"
#include <GL/glew.h>
#include "../util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../types.h"
#include "../shader.h"

class ShadowSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<GeoComponent> geoMapper;
    GLenum error;
    void vaoSetup(GLuint vao, GLuint vbo, GLuint ibo); // need this?
    GLuint fbo;
    GLuint vao;
    glm::mat4 MVP;
    glm::mat4 shadowMatrix;
    glm::mat4 MV;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 perspective;
    Shader shadowShader;
    float rot;
    GLuint depthMap;
    glm::mat4 shadowBias;
    glm::mat4 lightPersp;
public:
    GLuint shadowMap; // gathered later by the compositer
    GLuint colorTex; // need this?
    ShadowSystem(GLuint& depthMap, glm::mat4 shadowMatrix);
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
    virtual void begin();
    virtual void end();
};

#endif