#include "camera.h"

Camera::Camera(){
    lookAtPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    eye = glm::vec3(0.0f, 0.0f, -10.0f);
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::lookAt(eye, lookAtPoint, upVector);
    // viewMatrix = glm::mat4(1.0f);

    h = 600;
    w = 800;
    perspective = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.f);
}

Camera::Camera(glm::vec3& initialPos){
    lookAtPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    eye = initialPos;
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::lookAt(eye, lookAtPoint, upVector);
    // viewMatrix = glm::mat4(1.0f);
}

void Camera::rotate(const glm::vec3& axis, const float& angle){
    glm::vec3 forward = glm::normalize(lookAtPoint - eye);
    glm::quat rot = glm::angleAxis(angle, axis);
    forward = rot * forward;
    lookAtPoint = eye + forward;
    viewMatrix = glm::lookAt(eye, lookAtPoint, upVector);
}

void Camera::pitch(const float& angle){
    glm::vec3 forward = glm::normalize(lookAtPoint - eye);
    glm::vec3 axis = glm::normalize(glm::cross(forward, upVector));
    glm::quat rot = glm::angleAxis(angle, axis);
    forward = rot * forward;
    lookAtPoint = eye + forward;
    viewMatrix = glm::lookAt(eye, lookAtPoint, upVector);
}

void Camera::yaw(const float& angle){
    glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 forward = glm::normalize(lookAtPoint - eye);
    glm::quat rot = glm::angleAxis(angle, axis);
    forward = rot * forward;
    lookAtPoint = eye + forward;
    viewMatrix = glm::lookAt(eye, lookAtPoint, upVector);
}

void Camera::strafe(const float& amount){
    glm::vec3 forward = glm::normalize(lookAtPoint - eye);
    glm::vec3 strafe = glm::normalize(glm::cross(forward, upVector));
    strafe *= amount;
    eye += strafe;
    lookAtPoint += strafe;
    viewMatrix = glm::lookAt(eye, lookAtPoint, upVector);
}

void Camera::translate(const float& amount){
    glm::vec3 forward = glm::normalize(lookAtPoint - eye);
    forward *= amount;
    lookAtPoint += forward;
    eye += forward;
    viewMatrix = glm::lookAt(eye, lookAtPoint, upVector);
}

void Camera::reset(){
    lookAtPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    eye = glm::vec3(0.0f, 0.0f, -10.0f);
    viewMatrix = glm::lookAt(eye, lookAtPoint, upVector);
}