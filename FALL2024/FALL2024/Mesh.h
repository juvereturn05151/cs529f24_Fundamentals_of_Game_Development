#pragma once

/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Description: Drawing mesh. This can be extendable to all drawing objects in the game.
*/

#include "Vector3.h"
#include <vector>
#include <glew/glew.h>
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

class Mesh {
protected:
    VAO* VAO1; // Vertex Array Object
    VBO* VBO1; // Vertex Buffer Object
    EBO* EBO1; // Element Buffer Object
    Material* material; // Material properties for the mesh
    std::vector<GLfloat> vertices; // Vertex data
    std::vector<GLuint> indices; // Index data for drawing elements
    Vector3 color; // Mesh color
    float alpha; // Transparency factor
    Shader* shader; // Shader program for rendering
    std::vector<GLfloat> textureCoor = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    }; // Default texture coordinates

public:
    // Constructor to initialize the mesh with color, transparency, and shader program
    Mesh(Vector3 color, float alpha, Shader* shaderProgram);

    // Setup the buffers for rendering (VBO, VAO, EBO, etc.)
    void setupBuffers();

    // Modify buffer data
    void editBuffers();

    // Cleanup resources (VAO, VBO, etc.)
    void cleanup();

    // Render the mesh
    virtual void draw();

    // Add a default texture
    void AddTexture();

    // Add a texture with a specified name
    void AddTexture(std::string textureName);

    // Add a texture with a specified name and format
    void AddTexture(std::string textureName, GLenum format);
};
