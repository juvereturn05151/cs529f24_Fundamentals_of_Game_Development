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

    // Iterate through each component in the vector and delete them
    for (Component* component : components)
    {
        delete component; // Free the dynamically allocated memory for each component
    }

    // Clear the vector to remove dangling pointers
    components.clear();
}

// Update function to handle physics and call the base class update
void GameObject::update(float deltaTime)
{
    if (physicsComp != NULL)
    {
        physicsComp->update(deltaTime);
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