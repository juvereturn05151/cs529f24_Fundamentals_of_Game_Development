#pragma once
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "Matrix4.h"
#include "Vector3.h"
#include"Node.h"

class Camera : public Node {
private:
    Vector3 position;  // Camera position
    Vector3 target;    // Camera target position (where the camera is looking at)
    Vector3 up;        // Up vector
    float fov;
    float aspectRatio;
    float near;
    float far;
    Matrix4<float> viewMatrix;       // View matrix
    Matrix4<float> projectionMatrix;  // Projection matrix
    GLint viewMatrixLoc;
    GLint projectionMatrixLoc;

public:
    Camera();
    Camera(GLint viewMatrixLoc, GLint projectionMatrixLoc);
    ~Camera();

    void update(float deltaTime) override;
    void updateAspectRatio(int windowHeight, int windowWidth);

    void setPosition(const Vector3& position);
    void setTarget(const Vector3& target);
    void setUpVector(const Vector3& up);
    void setPerspective(float fov, float near, float far);

    const Matrix4<float>& getViewMatrix() const;
    const Matrix4<float>& getProjectionMatrix(float fov, float aspectRatio, float near, float far)  const;
};