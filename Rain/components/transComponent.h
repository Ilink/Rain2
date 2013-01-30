#ifndef TRANS_COMPONENT_H
#define TRANS_COMPONENT_H

#include <GL/glew.h>
#include "../include/Artemis-Cpp/Component.h"
// #include <Artemis-Cpp/Component.h>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
// i might need to make another one of these for the model-view part
class TransComponent : public artemis::Component{
public:
    glm::mat4 trans;

    TransComponent(glm::mat4& trans){
        this->trans = trans;
    };

    TransComponent(){
        this->trans = glm::mat4(1.0f); // identity
    };

    ~TransComponent(){

    };
};

#endif