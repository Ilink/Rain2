#ifndef RENDER_H
#define RENDER_H

#include "../Artemis-Cpp/Artemis.h"
#include "../components/geoComponent.h"
#include "../components/phongComponent.h"
#include <GL/glew.h>
#include "../util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../types.h"

class RenderSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<GeoComponent> geoMapper;
    artemis::ComponentMapper<PhongComponent> phongMapper;
    GLenum error;
    glm::mat4 perspective;
    glm::mat4 MV;
    glm::mat4 view;
    float rot;
    void vaoSetup(GLuint vao, GLuint vbo, GLuint ibo);
public:
    RenderSystem();
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
};

#endif