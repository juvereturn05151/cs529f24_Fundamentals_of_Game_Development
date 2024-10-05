#include "ObjectMesh.h"

ObjectMesh::ObjectMesh(Mesh* mesh) : mesh(mesh)
{

}

// Destructor
ObjectMesh::~ObjectMesh() {
    // Delete the mesh object to free memory
    delete mesh;
}

void ObjectMesh::draw()
{
    mesh->draw();
}

//Doesn't work, I wanna ask prosfessor why
void ObjectMesh::draw(GLint modelMatrixLoc)
{
    Matrix4<float> modelMatrix = getTransform().getModelMatrix();
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix.getData());
        mesh->draw();
}

void ObjectMesh::cleanup()
{
    mesh->cleanup();
}