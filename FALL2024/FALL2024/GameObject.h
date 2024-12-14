/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Description: GameObject class that allows for the addition of components such as Mesh and Physics.
             It inherits from the Node class and is intended to represent an object in the game world.
*/

#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Node.h"
#include "Mesh.h"
#include "PhysicsComponent.h"

class GameObject : public Node {
private:
    // Location of the model matrix in the shader (used for transforming the object in the GPU)
    GLint modelMatrixLoc;

protected:
    // Pointer to the Mesh instance that represents the visual component of this object
    Mesh* mesh = nullptr;

    // Pointer to the PhysicsComponent that handles the physics behavior of this object
    PhysicsComponent* physicsComp = nullptr;

public:
    // Default constructor: Initializes the GameObject without any mesh or physics component
    GameObject();

    // Constructor that initializes the GameObject with a specific Mesh
    explicit GameObject(Mesh* mesh);

    // Constructor that initializes the GameObject with both a Mesh and model matrix location for shaders
    GameObject(Mesh* mesh, GLint modelMatrixLoc);

    // Destructor: Cleans up the resources used by the GameObject
    ~GameObject();

    // Updates the GameObject, including its components, based on the deltaTime
    void update(float deltaTime) override;

    // Draws the GameObject (renders it to the screen), including its Mesh
    void draw() override;

    // Cleans up the resources used by the GameObject, particularly the components attached to it
    virtual void cleanup();

    // Adds a PhysicsComponent to the GameObject with the specified mass
    void addPhysicsComponent(float mass);

    // Retrieves the PhysicsComponent attached to this GameObject
    PhysicsComponent* getPhysicsComp();
};
#endif // !GAMEOBJECT_H