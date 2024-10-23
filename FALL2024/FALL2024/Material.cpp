#include "Material.h"

Material::Material(Shader* shaderProgram) : shader(shaderProgram)
{

}

void Material::Draw()
{
    if (shader != NULL)
    {
        GLint isUsingTexture = glGetUniformLocation(shader->ID, "useTexture");
        glUniform1i(isUsingTexture, hasTexture);
    }

    if (texture != NULL)
    {
        texture->Bind();
    }
}

void Material::Delete()
{
    if (texture != NULL)
    {
        texture->Delete();
    }
}

void Material::SetShader(Shader* shaderProgram)
{
    shader = shaderProgram;
}

void Material::AddTexture()
{
    hasTexture = true;
    texture = new Texture("Ryu2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texture->texUnit(*shader, "tex0", 0);
}