#include "PhysicsComponent.h"
#include "GameObject.h"
#include "GameConfig.h"

PhysicsComponent::PhysicsComponent(GameObject& _owner, float mass) : Component(_owner), mass(mass)
{
	velocity = Vector3(0, 0, 0);
}

void PhysicsComponent::update(float deltaTime)
{
	if (!isActive) 
	{
		return;
	}

	Vector3 gravity(0.0f, -20.0f * mass, 0.0f);
	accumulatedForce += gravity;

	Vector3 acceleration = accumulatedForce / mass;

	velocity += acceleration * deltaTime;

	// Apply damping to simulate friction, reducing velocity over time
	float dampingFactor = 0.98f; // Adjust based on desired friction level
	velocity *= dampingFactor;

	Vector3 pos = owner->getTransform()->getPosition();
	pos.x += velocity.x * deltaTime;
	pos.y += velocity.y * deltaTime;

	// Clamp the y position to ensure it doesn't go below 0
	if (pos.y < GROUND_HEIGHT) 
	{
		pos.y = GROUND_HEIGHT;
		velocity.y = 0.0f; // Reset the y velocity to prevent bouncing below the ground
	}

	owner->getTransform()->setPosition(pos);

	// Reset accumulated force for next frame
	accumulatedForce = Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsComponent::applyForce(const Vector3& force) 
{
	accumulatedForce = accumulatedForce + force;
}

void PhysicsComponent::setVelocity(const Vector3& velocity) 
{
	this->velocity = velocity;
}

Vector3 PhysicsComponent::getVelocity() const 
{
	return velocity;
}

float PhysicsComponent::getMass() const 
{
	return mass;
}