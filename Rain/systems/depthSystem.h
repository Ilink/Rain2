#ifndef DEPTHSYSTEM_H
#define DEPTHSYSTEM_H

#include "../Artemis-Cpp/Artemis.h"
#include "../components/geoComponent.h"
#include "../components/phongComponent.h"
#include "../components/transformationComponent.h"
#include <GL/glew.h>
#include "../util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../types.h"
#include "../shader.h"
#include "../spotlight.h"
#include "../settings.h"

class DepthSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<GeoComponent> geoMapper;
    artemis::ComponentMapper<TransformationComponent> transformationMapper;
    
    GLenum error;
    void vaoSetup(GLuint vao, GLuint vbo, GLuint ibo); // need this?
    GLuint fbo;
    GLuint vao;
    glm::mat4 MV;
    glm::mat4 view;
    glm::mat4 shadowView;
    glm::mat4 perspective;
    glm::mat4* viewMatrix;
    glm::mat4 model;
    Shader depthShader;
    float rot;
    float depth;
    Spotlight light;
public:
    glm::mat4 shadowMVP;
    GLuint depthMap;
    GLuint colorTex;
    DepthSystem(Spotlight& light, glm::mat4* viewMatrix);
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
    virtual void begin();
    virtual void end();
};

#endif