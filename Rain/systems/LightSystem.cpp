#include "LightSystem.h"

LightSystem::LightSystem(){
    // Artemis Setup
    perspective = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.f);
}

void LightSystem::initialize(){
    // movementMapper.init(*world);
}

void LightSystem::begin(){

}

void LightSystem::end(){
}

void LightSystem::processEntity(artemis::Entity &e){
}