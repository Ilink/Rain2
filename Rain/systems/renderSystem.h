/*
Rendering system.
*/

#ifndef RENDER_H
#define RENDER_H

#include "../Artemis-Cpp/Artemis.h"
#include "../components/geoComponent.h"
#include "../components/phongComponent.h"
#include <GL/glew.h>
#include "../util.h"

class RenderSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<GeoComponent> geoMapper;
    artemis::ComponentMapper<PhongComponent> phongMapper;
    GLenum error;
public:
    RenderSystem();
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
};

#endif