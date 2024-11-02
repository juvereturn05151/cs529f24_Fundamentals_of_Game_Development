#pragma once

#include "Node.h"
#include "Mesh.h"
#include "PhysicsComponent.h"

class GameObject : public Node {
private:
    Mesh* mesh = nullptr;  // Pointer to a Mesh instance, initialized to nullptr
    GLint modelMatrixLoc;

protected:
    PhysicsComponent* physicsComp = nullptr;  // Initialized to nullptr

public:
    GameObject();
    explicit GameObject(Mesh* mesh);
    GameObject(Mesh* mesh, GLint modelMatrixLoc);
    ~GameObject();

    void update(float deltaTime) override;
    void draw() override;
    virtual void cleanup();

    void addPhysicsComponent(float mass);
    PhysicsComponent* getPhysicsComp();
};