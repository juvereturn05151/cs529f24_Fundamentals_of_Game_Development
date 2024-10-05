#include "Camera.h"
#include <cmath> // For M_PI

Camera::Camera() : position(0.0f, 0.0f, -5.0f), target(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f) {

}

Camera::~Camera() {}

void Camera::setPosition(const Vector3& position) {
    this->position = position;
}

void Camera::setTarget(const Vector3& target) {
    this->target = target;
}

void Camera::setUpVector(const Vector3& up) {
    this->up = up;
}

const Matrix4<float>& Camera::getViewMatrix() const {
    return Matrix4<float>::lookAt(position, target, up);
}

const Matrix4<float>& Camera::getProjectionMatrix(float fov, float aspectRatio, float near, float far) const {
    return Matrix4<float>::perspective(fov, aspectRatio, near, far);
}