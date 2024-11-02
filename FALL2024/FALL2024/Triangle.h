#pragma once

#include "Mesh.h"
#include "Vector3.h"

class Triangle : public Mesh {
private:
    // Define default triangle vertices
    const std::vector<GLfloat> triangleVertices = 
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

public:
    Triangle(const Vector3& point1, const Vector3& point2, const Vector3& point3, const Vector3& color, float alpha, Shader* shaderProgram);
    Triangle(const Vector3& color, float alpha, Shader* shaderProgram);
};