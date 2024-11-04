#pragma once
#include "Vector3.h"
#include "Transform.h"

class PhysicsComponent
{
private:
	Vector3 velocity;
	float mass;
	Vector3 accumulatedForce;
	bool isActive;

public:

	PhysicsComponent(float mass);
	void update(Transform* transform, float deltaTime);
	void applyForce(const Vector3& force);
	void setVelocity(const Vector3& velocity);

	Vector3 getVelocity() const;
	float getMass() const;


};

