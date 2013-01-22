/*
shader stuff goes here
*/

#ifndef RENDERABLE_COMPONENT_H
#define RENDERABLE_COMPONENT_H

#include "../shader.h"
#include <GL/glew.h>
#include <Artemis-Cpp/Artemis.h>
#include <string>
#include <vector>

using namespace std;

class RenderableComponent : public artemis::Component{
public:
    Shader shader;
    Mesh mesh;

    RenderableComponent(const char* vsFilename, const char* fsFilename){
        this->shader.load(vsFilename, fsFilename);

    };
    ~RenderableComponent(){};
};

#endif