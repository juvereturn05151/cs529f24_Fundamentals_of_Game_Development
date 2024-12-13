#pragma once

/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Description: GameObject, must be able to add additional components
*/

#include "Node.h"
#include "Mesh.h"
#include "PhysicsComponent.h"

class GameObject : public Node {
private:
    GLint modelMatrixLoc;

protected:
    Mesh* mesh = nullptr;  // Pointer to a Mesh instance, initialized to nullptr
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