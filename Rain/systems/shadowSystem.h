#ifndef SHADOWSYSTEM_H
#define SHADOWSYSTEM_H

class ShadowSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<GeoComponent> geoMapper;
    artemis::ComponentMapper<PhongComponent> phongMapper;
    GLenum error;
    glm::mat4 MVP;
    glm::mat4 MV;
    void vaoSetup(GLuint vao, GLuint vbo, GLuint ibo);
public:
    RenderSystem();
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
};

#endif