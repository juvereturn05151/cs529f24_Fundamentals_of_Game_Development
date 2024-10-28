#include "ObjectMesh.h"

ObjectMesh::ObjectMesh()
{

}

ObjectMesh::ObjectMesh(Mesh* mesh) : mesh(mesh)
{

}

ObjectMesh::ObjectMesh(Mesh* mesh, GLint modelMatrixLoc) : mesh(mesh), modelMatrixLoc(modelMatrixLoc)
{

}

// Destructor
ObjectMesh::~ObjectMesh() {
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

void ObjectMesh::update(float deltaTime)
{
    if (physicsComp != NULL)
    {
        physicsComp->update(getTransform(), deltaTime);
    }

    Node::update(deltaTime);
}

void ObjectMesh::draw()
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

void ObjectMesh::cleanup()
{
    if (mesh != NULL)
    {
        mesh->cleanup();
    }
}

void ObjectMesh::addPhysicsComponent(float mass)
{
    if (physicsComp != NULL)
    {
        return;
    }

    physicsComp = new PhysicsComponent(mass);
}

PhysicsComponent* ObjectMesh::GetPhysicsComp()
{
    return physicsComp;
}