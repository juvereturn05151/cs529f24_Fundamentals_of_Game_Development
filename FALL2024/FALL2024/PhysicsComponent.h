#pragma once
#include "Vector3.h"
#include "ObjectMesh.h"

class PhysicsComponent
{
	PhysicsComponent(ObjectMesh* objectMesh, float mass);
	void update(float deltaTime);
	void applyForce(const Vector3& force);
	void setVelocity(const Vector3& velocity);

	Vector3 getVelocity() const;
	float getMass() const;

private:
	ObjectMesh* objectMesh;
	Vector3 velocity;
	float mass;
	Vector3 accumulatedForce;
};

