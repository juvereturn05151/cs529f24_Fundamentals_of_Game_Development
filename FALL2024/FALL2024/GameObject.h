#pragma once

#include"Node.h"
#include "PhysicsComponent.h"
class GameObject : public Node {
private:
    Mesh* mesh;  // Pointer to a Mesh instance
    GLint modelMatrixLoc;
    PhysicsComponent* physicsComp;

public:
    GameObject();
    GameObject(Mesh* mesh);
    GameObject(Mesh* mesh, GLint modelMatrixLoc);
    ~GameObject();
    void update(float deltaTime) override;
    void draw() override;
    virtual void cleanup();

    void addPhysicsComponent(float mass);
    PhysicsComponent* GetPhysicsComp();
};

