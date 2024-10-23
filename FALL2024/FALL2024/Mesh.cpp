#include "Mesh.h"

Mesh::Mesh(Vector3 color, float alpha, Shader* shaderProgram) : color(color), alpha(alpha), shader(shaderProgram)
{
    material = new Material(shaderProgram);
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

void  Mesh::editBUffers()
{
    VAO1->Bind();
    VBO1->EditVBO(&vertices[0], vertices.size() * sizeof(GLfloat));
    EBO1->EditEBO(&indices[0], indices.size() * sizeof(GLfloat));

    VAO1->LinkAttrib(*VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
    VAO1->LinkAttrib(*VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1->LinkAttrib(*VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
}

void Mesh::draw()
{
    if (VAO1 == NULL)
    {
        return;
    }

    if (material != NULL) 
    {
        material->Draw();
    }

    VAO1->Bind();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::cleanup() 
{
    // Cleanup the buffers if necessary
    if (VAO1 != NULL) 
    {
        VAO1->Delete();
        delete VAO1;
    }

    if (VBO1 != NULL)
    {
        VBO1->Delete();
        delete VBO1;
    }

    if (EBO1 != NULL)
    {
        EBO1->Delete();
        delete EBO1;
    }

    if (material != NULL)
    {
        material->Delete();
        delete material;
    }
}

void Mesh::AddTexture()
{
    if (material != NULL)
    {
        material->AddTexture();
    }
}