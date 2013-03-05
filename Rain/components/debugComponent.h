#ifndef DEBUGCOMPONENT_H
#define DEBUGCOMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class DebugComponent : public artemis::Component {
public:
    vec4 *color;

    DebugComponent(vec4* color){
        this->color = color;
    };

    ~DebugComponent(){

    };
};

#endif