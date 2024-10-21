#include "Square.h"

Square::Square(Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4, Vector3 color, float alpha) : Mesh(color, alpha)
{
    vertices =
    {
        point1.x, point1.y, point1.z, color.x, color.y, color.z, alpha, //0.0f, 0.0f,
        point2.x, point2.y, point2.z, color.x, color.y, color.z, alpha, //0.0f, 0.0f,
        point3.x, point3.y, point3.z, color.x, color.y, color.z, alpha, //1.0f, 1.0f,
        point4.x, point4.y, point4.z, color.x, color.y, color.z, alpha//, 1.0f, 0.0f
    };

    indices =
    {
        0, 1, 2,  // Define the triangle using vertex indices
        0, 3, 2
    };

    setupBuffers();
}

void Square::draw()
{
    if (VAO1 == NULL)
    {
        return;
    }

    VAO1->Bind();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}