#pragma once

#include"Node.h"
#include "PhysicsComponent.h"
class ObjectMesh : public Node {
private:
    Mesh* mesh;  // Pointer to a Mesh instance
    GLint modelMatrixLoc;
    PhysicsComponent* physicsComp;

public:
    ObjectMesh();
    ObjectMesh(Mesh* mesh);
    ObjectMesh(Mesh* mesh, GLint modelMatrixLoc);
    ~ObjectMesh();
    void update(float deltaTime) override;
    void draw() override;
    virtual void cleanup();

    void addPhysicsComponent(float mass);
    PhysicsComponent* GetPhysicsComp();
};

