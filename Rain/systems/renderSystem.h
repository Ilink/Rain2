/*
Rendering system.
*/

#ifndef RENDER_H
#define RENDER_H

#include <Artemis-Cpp/Artemis.h>
#include "../components/geoComponent.h"
#include "../components/renderableComponent.h"

class RenderSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<GeoComponent> geoMapper;
    artemis::ComponentMapper<RenderableComponent> renderableMapper;

public:
    RenderSystem();
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
};

#endif