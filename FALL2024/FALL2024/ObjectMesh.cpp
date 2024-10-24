#include "ObjectMesh.h"

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
}

void ObjectMesh::draw()
{
    Matrix4<float> modelMatrix = getGlobalModelMatrix();
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix.getData());
    
    if (mesh != NULL) 
    {
        mesh->draw();
    }

    Node::draw();
}

void ObjectMesh::cleanup()
{
    if (mesh != NULL)
    {
        mesh->cleanup();
    }
}