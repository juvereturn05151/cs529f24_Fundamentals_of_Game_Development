#include "Mesh.h"

Mesh::Mesh(Vector3 color, float alpha) : color(color), alpha(alpha)
{

}

void Mesh::setupBuffers() 
{
    VAO1 = new VAO();
    VAO1->Bind();

    VBO1 = new VBO(&vertices[0], vertices.size() * sizeof(GLfloat));
    EBO1 = new EBO(&indices[0], indices.size() * sizeof(GLuint));

    VAO1->LinkAttrib(*VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
    VAO1->LinkAttrib(*VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1->LinkAttrib(*VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
}

void Mesh::SetShader(Shader* shaderProgram)
{
    shader = shaderProgram;
}

void Mesh::draw()
{
    if (VAO1 == NULL)
    {
        return;
    }

    if (shader != NULL) 
    {
        GLint isUsingTexture = glGetUniformLocation(shader->ID, "useTexture");
        glUniform1i(isUsingTexture, hasTexture);
    }


    if (texture != NULL)
    {
        std::cout << "texture draw";
        texture->Bind();
    }
    else 
    {
        std::cout << "no draw";
    }

    VAO1->Bind();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void Mesh::cleanup() 
{
    // Cleanup the buffers if necessary
    VAO1->Delete();
    VBO1->Delete();
    EBO1->Delete();

    if (texture != NULL) 
    {
        texture->Delete();
    }
}

void Mesh::AddTexture(Shader *shaderProgram)
{
    GLint isUsingTexture = glGetUniformLocation(shaderProgram->ID, "useTexture");
    glUniform1i(isUsingTexture, true);
    hasTexture = true;
    texture = new Texture("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texture->texUnit(*shaderProgram, "tex0", 0);
}