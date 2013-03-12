#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include <GL/glew.h>
#include <Component.h>
#include <vector>
#include "../types.h"

using namespace std;

class MovementComponent : public artemis::Component {
public:

    MovementComponent(){
        
    };

    ~MovementComponent(){};
};

#endif