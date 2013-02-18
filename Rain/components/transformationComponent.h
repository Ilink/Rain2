#ifndef TRANSFORMATIONCOMPONENT_H
#define TRANSFORMATIONCOMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

class TransformationComponent : public artemis::Component {
public:
    float x;
    float y;
    float z;
    glm::mat4 modelMatrix;

    TransformationComponent(glm::vec3& pos){
        // this->x = pos[0];
        // this->y = pos[1];
        // this->z = pos[3];
        this->modelMatrix = glm::translate(glm::mat4(1.0f), pos);
    };

    TransformationComponent(glm::vec3& pos, float angle, glm::vec3& axis){
        // this->x = x;
        // this->y = y;
        // this->z = z;
        this->modelMatrix = glm::translate(glm::mat4(1.0f), pos);
        this->modelMatrix = glm::rotate(this->modelMatrix, angle, axis);
    };

    /*glm::mat4 getModelMatrix(){
        return glm::mat4(glm::mat4(1.0f), x, y, z);
    }*/

    ~TransformationComponent(){

    };
};

#endif