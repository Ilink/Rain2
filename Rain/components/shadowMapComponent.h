#ifndef SHADOWMAP_COMPONENT_H
#define SHADOWMAP_COMPONENT_H

#include <GL/glew.h>
#include "../include/Artemis-Cpp/Component.h"
#include <vector>
#include "../types.h"

using namespace std;

class ShadowMapComponent : public artemis::Component {
public:
	GLuint shadowMap;

    ShadowMapComponent(){
        
    };

    ~ShadowMapComponent(){
        // i guess destroy the shadowmap? make the opengl calls etc
    };
};

#endif