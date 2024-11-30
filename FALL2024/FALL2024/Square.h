#pragma once

#include "Mesh.h"

class Square : public Mesh {
protected:
    // Default vertices for a unit square centered at the origin
    std::vector<GLfloat> squareVertices =
    {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

public:
    Square(const Vector3& color, float alpha, Shader* shaderProgram);
    Square(const Vector3& point1, const Vector3& point2, const Vector3& point3, const Vector3& point4, const Vector3& color, float alpha, Shader* shaderProgram);
};