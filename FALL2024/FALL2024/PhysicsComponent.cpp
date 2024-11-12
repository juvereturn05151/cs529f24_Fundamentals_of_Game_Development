#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(float mass) 
{
	isActive = true;
	this->mass = mass;
	velocity = Vector3(0, 0, 0);
}

void PhysicsComponent::update(Transform* transform, float deltaTime)
{
	if (!isActive) 
	{
		return;
	}

	Vector3 gravity(0.0f, -20.0f * mass, 0.0f);
	accumulatedForce += gravity;

	Vector3 acceleration = accumulatedForce / mass;
	/*printf("accelerationX %f \n", acceleration.x);
	printf("deltaTime %f \n", deltaTime);*/
	velocity += acceleration * deltaTime;

	// Apply damping to simulate friction, reducing velocity over time
	float dampingFactor = 0.98f; // Adjust based on desired friction level
	velocity *= dampingFactor;

	//printf("velocity %f \n", velocity.x);
	Vector3 pos = transform->getPosition();
	pos.x += velocity.x * deltaTime;
	pos.y += velocity.y * deltaTime;

	// Clamp the y position to ensure it doesn't go below 0
	if (pos.y < -1.75f) 
	{
		pos.y = -1.75f;
		velocity.y = 0.0f; // Reset the y velocity to prevent bouncing below the ground
	}

	transform->setPosition(pos);

	// Reset accumulated force for next frame
	accumulatedForce = Vector3(0.0f, 0.0f, 0.0f);
}

void PhysicsComponent::applyForce(const Vector3& force) 
{
	accumulatedForce = accumulatedForce + force;
	//printf("apply force %i \n", accumulatedForce.x);
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

void PhysicsComponent::setIsActive(bool active)
{
	isActive = active;
}