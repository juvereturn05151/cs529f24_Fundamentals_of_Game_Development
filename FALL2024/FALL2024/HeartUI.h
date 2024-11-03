#pragma once
#include"Vector3.h"
#include"GameObject.h"
#include "Renderer.h"
#include "Square.h"
class HeartUI : public GameObject
{
public:
	HeartUI(Mesh* mesh, GLint modelMatrixLoc, Renderer& renderer, Vector3 pos);
};

