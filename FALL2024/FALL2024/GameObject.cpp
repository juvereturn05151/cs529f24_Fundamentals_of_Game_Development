#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(Mesh* mesh) : mesh(mesh)
{

}

GameObject::GameObject(Mesh* mesh, GLint modelMatrixLoc) : mesh(mesh), modelMatrixLoc(modelMatrixLoc)
{

}

// Destructor
GameObject::~GameObject() {
    // Delete the mesh object to free memory
    cleanup();

    if (mesh != NULL)
    {
        delete mesh;
    }

    if (physicsComp != NULL)
    {
        delete physicsComp;
    }
}

void GameObject::update(float deltaTime)
{
    if (physicsComp != NULL)
    {
        physicsComp->update(getTransform(), deltaTime);
    }

    Node::update(deltaTime);
}

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

void GameObject::cleanup()
{
    if (mesh != NULL)
    {
        mesh->cleanup();
    }
}

void GameObject::addPhysicsComponent(float mass)
{
    if (physicsComp != NULL)
    {
        return;
    }

    physicsComp = new PhysicsComponent(mass);
}

PhysicsComponent* GameObject::GetPhysicsComp()
{
    return physicsComp;
}

