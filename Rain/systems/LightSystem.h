#ifndef LIGHTSYSTEM_H
#define LIGHTSYSTEM_H

#include "../Artemis-Cpp/Artemis.h"
#include "../components/LightComponent.h"
#include "../components/TransformationComponent.h"
#include <GL/glew.h>
#include "../util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../types.h"
#include "../settings.h"
#include "GBufferSystem.h"

class LightSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<TransformationComponent> transMapper;
    glm::mat4 perspective;
    GLuint uMVPmat;
    GLuint uMVMatrix;
    GLuint uNormalMatrix;
    GLuint fbo;
    Shader shader;
    Camera& camera;
    glm::mat4 model;
    glm::mat4 MV;
public:
    // GBuffer& gBuffer;

    LightSystem(Camera& cam);
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
    virtual void begin();
    virtual void end();
};

#endif