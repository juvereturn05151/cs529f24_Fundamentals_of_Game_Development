#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(ObjectMesh* objectMesh, float mass) 
{
	this->objectMesh = objectMesh;
	this->mass = mass;
}

void PhysicsComponent::update(float deltaTime) 
{
	Vector3 acceleration = accumulatedForce / mass;
	velocity += acceleration * deltaTime;
	Vector3 pos = objectMesh->getTransform()->getPosition();
	objectMesh->getTransform()->setPosition(Vector3(pos.x + (velocity.x * deltaTime), pos.y + (velocity.y * deltaTime),0));

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