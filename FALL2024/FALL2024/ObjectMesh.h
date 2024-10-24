#pragma once

#include"Node.h"
class ObjectMesh : public Node {
private:
    Mesh* mesh;  // Pointer to a Mesh instance
    GLint modelMatrixLoc;

public:
    ObjectMesh(Mesh* mesh);
    ObjectMesh(Mesh* mesh, GLint modelMatrixLoc);
    ~ObjectMesh();
    void draw() override;
    virtual void cleanup();
};

