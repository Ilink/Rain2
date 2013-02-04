#ifndef POINTLIGHT_COMPONENT_H
#define POINTLIGHT_COMPONENT_H

#include <GL/glew.h>
#include "../include/Artemis-Cpp/Component.h"
#include <vector>
#include "../types.h"

using namespace std;

class PointLightComponent : public artemis::Component {
public:
    Color color;
    double brightness;

    PointLightComponent(double brightness, Color color){
        this->brightness = brightness;
        this->color = color;
    };

    ~PointLightComponent(){

    };
};

#endif