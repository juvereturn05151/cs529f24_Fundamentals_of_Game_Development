#pragma once
#include "Vector3.h"
#include <vector>
#include <glew/glew.h>
#include "VAO.h"
#include "EBO.h"

class Mesh {
public:
    VAO* VAO1;
    VBO* VBO1;
    EBO* EBO1;
    Vector3 point1;
    Vector3 point2;
    Vector3 point3;
    Vector3 color;
    float alpha;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    Mesh(Vector3 point1, Vector3 point2, Vector3 point3,Vector3 color, float alpha);
    void setupBuffers(); // Setup VBO, VAO, etc.
    void cleanup(); // Cleanup resources
    void draw();
};