#ifndef GBufferSystem_H
#define GBufferSystem_H

#include "../Artemis-Cpp/Artemis.h"
#include "../components/MovementComponent.h"
#include "../components/geoComponent.h"
#include "../components/transformationComponent.h"
#include <GL/glew.h>
#include "../util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../types.h"
#include "../settings.h"
#include "../shader.h"
#include "../camera.h"

class GBufferSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<GeoComponent> geoMapper;
    artemis::ComponentMapper<TransformationComponent> transMapper;
    glm::mat4 perspective;
    GLuint uMVPmat;
    GLuint uMVMatrix;
    GLuint uVMatrix;
    GLuint uNormalMatrix;
    GLuint fbo;
    Shader shader;
    Camera& camera;
    glm::mat4 model;
    glm::mat4 MV;
public:
    GBuffer gBuffer;

    GBufferSystem(Camera& cam);
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
    virtual void begin();
    virtual void end();
};

#endif