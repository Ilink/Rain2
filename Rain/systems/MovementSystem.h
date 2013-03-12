#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Artemis-Cpp/Artemis.h"
#include "../components/MovementComponent.h"
#include <GL/glew.h>
#include "../util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../types.h"
#include "../settings.h"

class MovementSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<MovementComponent> movementMapper;

public:
    MovementSystem();
    virtual void initialize();
    virtual void processEntity(artemis::Entity &e);
    virtual void begin();
    virtual void end();
};

#endif