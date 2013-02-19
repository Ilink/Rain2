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
    glm::vec3 *pos;
    glm::mat4 *modelMatrix;
    glm::vec3 *axis;
    float *angle;

    TransformationComponent(glm::vec3* pos){
        // this->x = pos[0];
        // this->y = pos[1];
        // this->z = pos[3];

        float angle = 0.0f;
        this->angle = &angle;
        this->axis = &glm::vec3(0.0f,0.0f,0.0f);
        this->pos = pos;
        this->modelMatrix = &glm::translate(glm::mat4(1.0f), *this->pos);
    };

    TransformationComponent(glm::vec3* pos, float* angle, glm::vec3* axis){
        // this->x = x;
        // this->y = y;
        // this->z = z;

        this->angle = angle;
        this->axis = axis;
        this->pos = pos;
        this->modelMatrix = &glm::translate(glm::mat4(1.0f), *this->pos);
        this->modelMatrix = &glm::rotate(*this->modelMatrix, *angle, *axis);
    };

    glm::mat4 getModelMatrix(){
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), *pos);
        if(*angle != 0.0){
            return glm::rotate(trans, *angle, *axis);
        } else {
            return trans;
        }
    }

    ~TransformationComponent(){

    };
};

#endif