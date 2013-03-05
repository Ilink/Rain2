#ifndef ID_COMPONENT_H
#define ID_COMPONENT_H

#include <GL/glew.h>
#include <Component.h>
#include <vector>
#include "../types.h"

using namespace std;

class IDComponent : public artemis::Component {
public:
    unsigned int id;

    IDComponent(unsigned int id){
        this->id = id;
    };

    ~IDComponent(){};
};

#endif