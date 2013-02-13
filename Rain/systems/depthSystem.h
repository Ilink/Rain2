#ifndef DEPTHSYSTEM_H
#define DEPTHSYSTEM_H

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

class DepthSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<GeoComponent> geoMapper;
    GLenum error;
    void vaoSetup(GLuint vao, GLuint vbo, GLuint ibo); // need this?
    GLuint fbo;
    GLuint vao;
    glm::mat4 MVP;
    glm::mat4 MV;
    Shader depthShader;
    float rot;
public:
    GLuint depthMap;
    GLuint colorTex;
    DepthSystem();
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
    virtual void begin();
    virtual void end();
};

#endif