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
    delete mesh;
}

void ObjectMesh::draw()
{
    Matrix4<float> modelMatrix = transform->getModelMatrix();
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix.getData());
    mesh->draw();
}

//Doesn't work, I wanna ask prosfessor why
void ObjectMesh::draw(GLint modelMatrixLoc)
{
    Matrix4<float> modelMatrix = getTransform()->getModelMatrix();
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix.getData());
        mesh->draw();
}

void ObjectMesh::cleanup()
{
    mesh->cleanup();
}