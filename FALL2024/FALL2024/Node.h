#pragma once
#include"Matrix4.h"
#include <vector>
#include "Transform.h"
#include"Mesh.h"
class Node
{
protected:
    Transform *transform;
    Node* parent = nullptr;
    std::vector<Node*> children;
    void setParent(Node* parent);
    Matrix4<float> getGlobalModelMatrix() const;
    GLint modelMatrixLoc;

public:
    Node();
    virtual ~Node();

    // Get access to the Transform object
    Transform *getTransform();

    virtual void update(float deltaTime);
    virtual void draw();

    void addChild(Node* child);

};
