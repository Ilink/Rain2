#include "renderSystem.h"

RenderSystem::RenderSystem(){
    addComponentType<GeoComponent>();
    addComponentType<RenderableComponent>();
}

virtual void RenderSystem::initialize(){
    geoMapper.init(*world);
}

virtual void processEntity(artemis::Entity &e){
    // geoMapper.get(e)->
}