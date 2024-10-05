#include "Mesh.h"

Mesh::Mesh(Vector3 point1, Vector3 point2, Vector3 point3, Vector3 color, float alpha) : point1(point1), point2(point2), point3(point3), color(color), alpha(alpha){
    setupBuffers();
}

void Mesh::setupBuffers() {
    GLfloat vertices[] =
    {
        point1.x, point1.y, point1.z, color.x, color.y, color.z, alpha,
        point2.x, point2.y, point2.z, color.x, color.y, color.z, alpha,
        point3.x, point3.y, point3.z, color.x, color.y, color.z, alpha
    };

    GLuint indices[] = {
        0, 1, 2  // Define the triangle using vertex indices
    };

    VAO1 = new VAO();
    VAO1->Bind();

    VBO1 = new VBO(vertices, sizeof(vertices));
    EBO1 = new EBO(indices, sizeof(indices));

    VAO1->LinkAttrib(*VBO1, 0, 3, GL_FLOAT, 7 * sizeof(float), (void*)0);
    VAO1->LinkAttrib(*VBO1, 1, 4, GL_FLOAT, 7 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Mesh::draw()
{
    VAO1->Bind();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void Mesh::cleanup() {
    // Cleanup the buffers if necessary
    VAO1->Delete();
    VBO1->Delete();
    EBO1->Delete();
}