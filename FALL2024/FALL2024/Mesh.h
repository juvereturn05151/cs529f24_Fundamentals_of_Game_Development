#pragma once
#include "Vector3.h"
#include <vector>
#include <glew/glew.h>
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

class Mesh 
{
protected:
    VAO* VAO1;
    VBO* VBO1;
    EBO* EBO1;
    Material* material;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    Vector3 color;
    float alpha;
    Shader* shader;
    std::vector<GLfloat> textureCoor =
    {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };


public:
    Mesh(Vector3 color, float alpha, Shader* shaderProgram);
    void setupBuffers(); // Setup VBO, VAO, etc.
    void editBUffers();
    void cleanup(); // Cleanup resources
    virtual void draw();
    void AddTexture();
};