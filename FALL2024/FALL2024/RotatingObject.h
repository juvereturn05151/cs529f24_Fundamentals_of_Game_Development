#pragma once
#include "GameObject.h"
#include "Mesh.h"
class RotatingObject : public GameObject
{
private:
	float angle;

public:
	RotatingObject(Mesh* mesh, GLint modelMatrixLoc);
	void update(float deltaTime) override;
};

