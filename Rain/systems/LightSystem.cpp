#include "LightSystem.h"

LightSystem::LightSystem(Camera& camera, GBuffer& gBuffer)
    :camera(camera),
    gBuffer(gBuffer)
{
    /////////////////////////////
    // Artemis Setup
    /////////////////////////////
    addComponentType<GeoComponent>();
    addComponentType<LightComponent>();
    addComponentType<TransformationComponent>();

    perspective = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.f);
}

void LightSystem::initialize(){
    lightMapper.init(*world);
    geoMapper.init(*world);
    transMapper.init(*world);
}

void LightSystem::begin(){

}

void LightSystem::end(){
}

void LightSystem::processEntity(artemis::Entity &e){
}