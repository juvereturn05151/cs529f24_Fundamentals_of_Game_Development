#include "GameObject.h"

// Constructors
GameObject::GameObject() = default;

GameObject::GameObject(Mesh* mesh)
    : mesh(mesh)
{
}

GameObject::GameObject(Mesh* mesh, GLint modelMatrixLoc)
    : mesh(mesh), modelMatrixLoc(modelMatrixLoc)
{
}

// Destructor
GameObject::~GameObject()
{
    cleanup();
    delete mesh;
    delete physicsComp;
}

// Update function to handle physics and call the base class update
void GameObject::update(float deltaTime)
{
    if (physicsComp != NULL)
    {
        physicsComp->update(getTransform(), deltaTime);
    }

    Node::update(deltaTime);
}

// Draw function to render the mesh and call the base class draw
void GameObject::draw()
{
    if (isActive)
    {
        Matrix4<float> modelMatrix = getGlobalModelMatrix();
        glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix.getData());

        if (mesh != NULL)
        {
            mesh->draw();
        }

        Node::draw();
    }
}

// Cleanup function to release mesh resources
void GameObject::cleanup()
{
    if (mesh != NULL)
    {
        mesh->cleanup();
    }
}

// Add a physics component to the GameObject, if one doesn't already exist
void GameObject::addPhysicsComponent(float mass)
{
    if (physicsComp == NULL)
    {
        physicsComp = new PhysicsComponent(mass);
    }
}

// Get the physics component
PhysicsComponent* GameObject::getPhysicsComp()
{
    return physicsComp;
}