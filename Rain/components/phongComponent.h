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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class PhongComponent : public artemis::Component{
public:
    Shader shader;
    double brightness;
    double specularity;
    glm::vec3 color;

    // filenames could be mapped elsewhere, so we can just say "phong"
    PhongComponent(const char* vsFilename, const char* fsFilename, const double& brightness, const double& specularity, const glm::vec3& color){
       this->brightness = brightness;
       this->specularity = specularity;
       this->shader.load(vsFilename, fsFilename);
       this->color = color;
    };

    // this lets you use preloaded/compiled shaders
    PhongComponent(Shader shader, const double& brightness, const double& specularity, const glm::vec3& color){
       this->brightness = brightness;
       this->specularity = specularity;
       this->shader = shader;
       this->color = color;
    };
    ~PhongComponent(){};
};

#endif