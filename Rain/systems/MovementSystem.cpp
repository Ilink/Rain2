#include "MovementSystem.h"

MovementSystem::MovementSystem(){
    // Artemis Setup
    addComponentType<MovementComponent>();
    
}

void MovementSystem::initialize(){
    movementMapper.init(*world);
}

void MovementSystem::begin(){

}

void MovementSystem::end(){
}

void MovementSystem::processEntity(artemis::Entity &e){
}