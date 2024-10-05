#pragma once
#include"Mesh.h"
#include"Node.h"
class ObjectMesh : public Node {
private:
    Mesh* mesh;  // Pointer to a Mesh instance

public:
    ObjectMesh(Mesh* mesh);
    ~ObjectMesh();
};

