/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Brief: Handles the physics behavior of a GameObject by managing forces, velocity, and updates based on the simulation's delta time.
*/

#pragma once

#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Vector3.h"    // For 3D vector math operations
#include "Transform.h"  // To modify GameObject's transformation properties
#include "Component.h"  // Base class for all components

// The PhysicsComponent class handles physics-related calculations for a GameObject.
// This includes velocity updates, force accumulation, and damping.
class PhysicsComponent : public Component {
private:
    const float dampingFactor = 0.98f; // A constant factor to simulate friction or air resistance
    Vector3 velocity;                  // The current velocity of the GameObject
    float mass;                        // The mass of the GameObject, used for force calculations
    Vector3 accumulatedForce;          // The sum of all forces applied during a single frame

public:
    // Constructor: Initializes the PhysicsComponent with an owner GameObject and its mass.
    PhysicsComponent(GameObject& _owner, float mass);

    // Initializes the PhysicsComponent. Can be extended for more complex setups.
    void initialize() {};

    // Updates the PhysicsComponent every frame.
    // - Integrates forces to compute velocity and position changes.
    // - Applies damping to slow the object over time.
    void update(float deltaTime);

    // Applies a force to the object. This force is added to the accumulatedForce.
    // Forces should be cleared each frame after being applied.
    void applyForce(const Vector3& force);

    // Sets the velocity of the object directly.
    void setVelocity(const Vector3& velocity);

    // Gets the current velocity of the object.
    Vector3 getVelocity() const;

    // Gets the mass of the object.
    float getMass() const;
};

#endif