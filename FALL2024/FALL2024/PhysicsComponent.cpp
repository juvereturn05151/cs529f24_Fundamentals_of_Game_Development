#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(float mass) 
{
	this->mass = mass;
	velocity = Vector3(0, 0, 0);
}

void PhysicsComponent::update(Transform* transform, float deltaTime)
{
	
	Vector3 acceleration = accumulatedForce / mass;
	printf("accelerationX %f \n", acceleration.x);
	printf("deltaTime %f \n", deltaTime);
	velocity += acceleration * deltaTime;
	printf("velocity %f \n", velocity.x);
	Vector3 pos = transform->getPosition();
	transform->setPosition(Vector3(pos.x + (velocity.x * deltaTime), pos.y + (velocity.y * deltaTime),0));

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