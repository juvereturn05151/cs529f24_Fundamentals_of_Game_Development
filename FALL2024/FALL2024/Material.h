#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Matrix4.h"
class Material
{
private:
	Shader* shader;
	bool hasTexture;
	Texture* texture;
	Matrix4<float> modelMatrix;
public:
	Material(Shader* shaderProgram);
	void Draw();
	void Delete();
	void AddTexture();
	void SetShader(Shader* shaderProgram);
};

