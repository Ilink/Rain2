#ifndef POINTLIGHT_COMPONENT_H
#define POINTLIGHT_COMPONENT_H

#include <GL/glew.h>
#include "Artemis.h"
#include <vector>
#include "../types.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class LightComponent : public artemis::Component {
public:
    glm::vec3& color;
    const float& brightness;
    // vector <vertex>& verts;
    // vector<GLuint>& triIndex;

    LightComponent(glm::vec3& color, const float& brightness)
        :color(color),
        brightness(brightness)
    {
    };

    ~LightComponent(){

    };
};

#endif