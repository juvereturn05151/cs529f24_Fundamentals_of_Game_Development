#pragma once
#include "Mesh.h"
class Square : public Mesh
{
	public:
		Square(Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4, Vector3 color, float alpha);
		void draw() override;
};

