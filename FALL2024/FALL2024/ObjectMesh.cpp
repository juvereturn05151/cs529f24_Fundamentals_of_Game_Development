#include "ObjectMesh.h"

ObjectMesh::ObjectMesh(Mesh* mesh) : mesh(mesh)
{

}

// Destructor
ObjectMesh::~ObjectMesh() {
    // Delete the mesh object to free memory
    delete mesh;
}