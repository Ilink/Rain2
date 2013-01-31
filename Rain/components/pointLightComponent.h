#ifndef POINTLIGHT_COMPONENT_H
#define POINTLIGHT_COMPONENT_H

#include <GL/glew.h>
#include "../include/Artemis-Cpp/Component.h"
#include <vector>
#include "../types.h"

using namespace std;

class PointLightComponent : public artemis::Component {
public:
    Position pos;
    Color color;
    double brightness;

    PointLight(Position pos, double brightness, Color color){
        this->pos = pos;
        this->brightness = brightness;
        this->color = color;
    };

    ~PointLight(){

    };
};

#endif