#pragma once
#include "Matrix4.h"
#include "Vector3.h"

class Camera {
public:
    Camera();
    ~Camera();

    void setPosition(const Vector3& position);
    void setTarget(const Vector3& target);
    void setUpVector(const Vector3& up);

    const Matrix4<float>& getViewMatrix() const;
    const Matrix4<float>& getProjectionMatrix(float fov, float aspectRatio, float near, float far)  const;

private:
    Vector3 position;  // Camera position
    Vector3 target;    // Camera target position (where the camera is looking at)
    Vector3 up;        // Up vector

    Matrix4<float> viewMatrix;       // View matrix
    Matrix4<float> projectionMatrix;  // Projection matrix
};