#include "Triangle.h"

Triangle::Triangle(Vector3 point1, Vector3 point2, Vector3 point3, Vector3 color, float alpha) : Mesh(color, alpha)
{
    vertices =
    {
        point1.x, point1.y, point1.z, color.x, color.y, color.z, alpha, 0.0f, 0.0f,
        point2.x, point2.y, point2.z, color.x, color.y, color.z, alpha, 0.0f, 0.0f,
        point3.x, point3.y, point3.z, color.x, color.y, color.z, alpha, 1.0f, 1.0f,
    };

    indices =
    {
        0, 1, 2  // Define the triangle using vertex indices
    };

    setupBuffers();
}