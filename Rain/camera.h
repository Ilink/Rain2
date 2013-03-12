#ifndef CAMERA_H
#define CAMERA_H

#include "../types.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera {
    glm::vec3 upVector;
    glm::vec3 lookAtPoint;
    glm::vec3 eye;
    float i;
public:
    Camera();
    Camera(glm::vec3& initialPos);
    void rotate(const glm::vec3& axis, const float& angle);
    void pitch(const float& angle);
    void yaw(const float& angle);
    void strafe(const float& amount);
    void translate(const float& amount);
    void reset();
    glm::mat4 perspective;
    glm::mat4 viewMatrix;
    int h; int w;
};

#endif