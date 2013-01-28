/*
shader stuff goes here
*/

#ifndef PHONG_COMPONENT_H
#define PHONG_COMPONENT_H

#include "../shader.h"
#include <GL/glew.h>
#include "../shader.h"
#include "../Artemis-Cpp/Artemis.h"
#include <string>
#include <vector>

using namespace std;

class PhongComponent : public artemis::Component{
public:
    Shader shader;
    double brightness;
    double specularity;

    // filenames could be mapped elsewhere, so we can just say "phong"
    PhongComponent(const char* vsFilename, const char* fsFilename, const double& brightness, const double& specularity){
       this->brightness = brightness;
       this->specularity = specularity;
       this->shader.load(vsFilename, fsFilename);
    };

    // this lets you use preloaded/compiled shaders
    PhongComponent(Shader shader, const double& brightness, const double& specularity){
       this->brightness = brightness;
       this->specularity = specularity;
       this->shader = shader;
    };
    ~PhongComponent(){};
};

#endif