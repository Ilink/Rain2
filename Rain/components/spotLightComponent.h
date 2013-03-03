#ifndef SPOTLIGHT_COMPONENT_H
#define SPOTLIGHT_COMPONENT_H

#include <GL/glew.h>
#include <Component.h>
#include <vector>
#include "../types.h"

using namespace std;

class SpotLightComponent : public artemis::Component {
public:
    Color color;
    double brightness;
    glm::vec3 lookAtPoint;
    glm::vec3 upVector;
    glm::vec3 position;

    SpotLightComponent(double brightness, Color color, glm::vec3 position, glm::vec3 lookAtPoint){
        this->brightness = brightness;
        this->color = color;
        this->position = position;
        this->lookAtPoint = lookAtPoint;
    };

    SpotLightComponent(double brightness, glm::vec3 position, glm::vec3 lookAtPoint){
        this->brightness = brightness;
        this->position = position;
        this->lookAtPoint = lookAtPoint;
    };

    ~SpotLightComponent(){

    };
};

#endif