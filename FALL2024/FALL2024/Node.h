#pragma once

/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Description: This is basically an empty game object. 
*/

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
    bool isActive = true;

public:
    Node();
    virtual ~Node();

    // Get access to the Transform object
    Transform *getTransform();
    void setIsActive(bool active);
    bool getIsActive();

    virtual void update(float deltaTime);
    virtual void draw();

    void addChild(Node* child);
    Vector3 getGlobalPosition() const;
};
