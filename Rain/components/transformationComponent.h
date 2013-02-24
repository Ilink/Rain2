#ifndef TRANSFORMATIONCOMPONENT_H
#define TRANSFORMATIONCOMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

class TransformationComponent : public artemis::Component {
public:
    glm::vec3 *pos;
    glm::vec3 *axis;
    glm::vec3 *scale;
    float *angle;

    TransformationComponent(glm::vec3* pos){
        this->pos = pos;

        this->scale = NULL;
        this->angle = NULL;
        this->axis = NULL;
    };

    TransformationComponent(glm::vec3* pos, float* angle, glm::vec3* axis){
        this->angle = angle;
        this->axis = axis;
        this->pos = pos;

        this->scale = NULL;
    };

    TransformationComponent(glm::vec3* pos, glm::vec3* scale){
        this->pos = pos;
        this->scale = scale;

        this->angle = NULL;
        this->axis = NULL;
    };

    TransformationComponent(glm::vec3* pos, glm::vec3* scale, float* angle, glm::vec3* axis){
        this->pos = pos;
        this->scale = scale;
        this->angle = angle;
        this->axis = axis;
    };

    glm::mat4 getModelMatrix(){
        glm::mat4 model = glm::translate(glm::mat4(1.0f), *pos);
        if(angle != NULL && axis != NULL){
            model = glm::rotate(model, *angle, *axis);
        }
        if(scale != NULL){
            model = glm::scale(model, *scale);
        }
        return model;
    };

    ~TransformationComponent(){

    };
};

#endif