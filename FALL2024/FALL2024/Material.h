#pragma once
#include "Texture.h"
#include "Shader.h"
class Material
{
private:
	Shader* shader;
	bool hasTexture;
	Texture* texture;
public:
	void Draw();
	void Delete();
	void AddTexture();
	void SetShader(Shader* shaderProgram);
};

