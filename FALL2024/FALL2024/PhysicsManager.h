#pragma once

#include "CollisionGenerator.h"
#include "EventManager.h"
#include "CollisionEvent.h"
#include <vector>

class PhysicsManager {
public:
    static PhysicsManager& Instance();

    void removeBody(PhysicsBody* body);

    void update(float deltaTime);

    const std::vector<PhysicsBody*>& getBodies() const { return bodies; }

    void addBody(PhysicsBody* physicsBody);

private:
    PhysicsManager() = default;
    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;

    void checkCollisions();

    std::vector<PhysicsBody*> bodies;
    CollisionGenerator collisionGenerator;
};