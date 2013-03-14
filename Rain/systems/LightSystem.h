#ifndef LIGHTSYSTEM_H
#define LIGHTSYSTEM_H

#include "../Artemis-Cpp/Artemis.h"
#include "../components/LightComponent.h"
#include "../components/geoComponent.h"
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
    artemis::ComponentMapper<GeoComponent> geoMapper;
    artemis::ComponentMapper<LightComponent> lightMapper;

    glm::mat4 perspective;
    GLuint uMVPmat;
    GLuint uMVMatrix;
    GLuint uNormalsSampler;
    GLuint uColorSampler;
    GLuint fbo;
    Shader lightShader;
    Camera& camera;
    glm::mat4 model;
    glm::mat4 MV;
public:
    GBuffer& gBuffer;

    LightSystem(Camera& cam, GBuffer& gBuffer);
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
    virtual void begin();
    virtual void end();
};

#endif