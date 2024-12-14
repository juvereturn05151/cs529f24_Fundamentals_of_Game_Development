#pragma once
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Vector3.h"
#include "Transform.h"
#include "Component.h"

class PhysicsComponent : public Component
{
private:
	const float dampingFactor = 0.98f;
	Vector3 velocity;
	float mass;
	Vector3 accumulatedForce;

public:

	PhysicsComponent(GameObject& _owner,float mass);
	void initialize() {};
	void update(float deltaTime);
	void applyForce(const Vector3& force);
	void setVelocity(const Vector3& velocity);

	Vector3 getVelocity() const;
	float getMass() const;
};

#endif