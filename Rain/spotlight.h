#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <GL/glew.h>
#include <vector>
#include "../types.h"

using namespace std;

class Spotlight {
public:
    double brightness;
    glm::vec3* lookAtPoint;
    glm::vec3 upVector;
    glm::vec3* position;
    glm::mat4 viewMatrix;
    glm::mat4 perspectiveMatrix;

    Spotlight(){};

    Spotlight(double brightness, glm::vec3* position, glm::vec3* lookAtPoint){
        this->perspectiveMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.f);
        this->upVector = glm::vec3(0.0f, 1.0f, 0.0f);
        // this->upVector = glm::vec3(0.0f, 0.0f, 1.0f);
        
        this->brightness = brightness;
        this->position = position;
        this->lookAtPoint = lookAtPoint;
        this->viewMatrix = glm::lookAt(*position, *lookAtPoint, upVector);
    };

    void rotate(double deg, glm::vec3 axis){
        /*
        glm::vec3 frontDirection = *lookAtPoint - *position;
        frontDirection = glm::normalize(frontDirection);

        vec3.normalize(frontDirection);
        var q = quat4.create();
        quat4.fromAngleAxis(deg, axis, q);
        quat4.multiplyVec3(q, frontDirection);
        lookAtPoint = vec3.create(eyePoint);
        vec3.add(lookAtPoint, frontDirection);
        */
    };

    void update(){
        this->viewMatrix = glm::lookAt(*position, *lookAtPoint, upVector);
    };

    ~Spotlight(){};
};

#endif