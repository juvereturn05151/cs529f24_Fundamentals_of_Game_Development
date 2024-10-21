#pragma once
#include "Vector3.h"
#include <vector>
#include <glew/glew.h>
#include "VAO.h"
#include "EBO.h"

class Mesh 
{
protected:
    VAO* VAO1;
    VBO* VBO1;
    EBO* EBO1;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    Vector3 color;
    float alpha;

public:
    Mesh(Vector3 color, float alpha);
    void setupBuffers(); // Setup VBO, VAO, etc.
    void cleanup(); // Cleanup resources
    virtual void draw();
};