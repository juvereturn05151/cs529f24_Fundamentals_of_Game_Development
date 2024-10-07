#pragma once
#include "Mesh.h"
#include "Vector3.h"
class Triangle : public Mesh
{
public:
	Triangle(Vector3 point1, Vector3 point2, Vector3 point3, Vector3 color, float alpha);
};

