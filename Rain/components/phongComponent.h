/*
shader stuff goes here
*/

#ifndef PHONG_COMPONENT_H
#define PHONG_COMPONENT_H

#include "../shader.h"
#include <GL/glew.h>
#include <Artemis-Cpp/Artemis.h>
#include <string>
#include <vector>

using namespace std;

class PhongComponent : public artemis::Component{
public:
    Shader shader;
    const double brightness;
    const double specularity;

    PhongComponent(const char* vsFilename, const char* fsFilename, const double& brightness, const double& specularity){
        this->shader.load(vsFilename, fsFilename);

    };
    ~PhongComponent(){};
};

#endif