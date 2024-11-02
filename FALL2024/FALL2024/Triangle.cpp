#include "Triangle.h"

// Constructor with default triangle vertices
Triangle::Triangle(const Vector3& color, float alpha, Shader* shaderProgram)
    : Mesh(color, alpha, shaderProgram)
{
    // Set vertices using default triangle vertices and color
    vertices =
    {
        triangleVertices[0], triangleVertices[1], triangleVertices[2], color.x, color.y, color.z, alpha, 0.0f, 0.0f,
        triangleVertices[3], triangleVertices[4], triangleVertices[5], color.x, color.y, color.z, alpha, 0.0f, 0.0f,
        triangleVertices[6], triangleVertices[7], triangleVertices[8], color.x, color.y, color.z, alpha, 1.0f, 1.0f
    };

    // Define indices for the triangle
    indices = { 0, 1, 2 };

    setupBuffers();
}

// Constructor with custom points
Triangle::Triangle(const Vector3& point1, const Vector3& point2, const Vector3& point3, const Vector3& color, float alpha, Shader* shaderProgram)
    : Mesh(color, alpha, shaderProgram)
{
    // Set vertices with given points and color
    vertices = 
    {
        point1.x, point1.y, point1.z, color.x, color.y, color.z, alpha, 0.0f, 0.0f,
        point2.x, point2.y, point2.z, color.x, color.y, color.z, alpha, 0.0f, 0.0f,
        point3.x, point3.y, point3.z, color.x, color.y, color.z, alpha, 1.0f, 1.0f
    };

    // Define indices for the triangle
    indices = { 0, 1, 2 };

    setupBuffers();
}

