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
    GLuint shadowMap;
    GLuint fbo;
    GLuint vao;
    glm::mat4 MVP;
    glm::mat4 MV;
    Shader shader;
    float rot;
public:
    ShadowSystem(GLuint& _shadowMap);
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
};

#endif