#pragma once

/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Description: This is an empty game object class, which can serve as a basic building block
             for a scene graph system, where each node can have a transform and child nodes.
*/

#include "Matrix4.h"
#include <vector>
#include "Transform.h"
#include "Mesh.h"

class Node
{
protected:
    // The transformation (position, rotation, scale) of this node
    Transform* transform;

    // The parent node of this node, if any
    Node* parent = nullptr;

    // A list of child nodes that are attached to this node
    std::vector<Node*> children;

    // Sets the parent node, ensuring the parent-child relationship is maintained
    void setParent(Node* parent);

    // Retrieves the global transformation matrix for this node, including the transformations of the parent chain
    Matrix4<float> getGlobalModelMatrix() const;

    // Indicates whether this node is active in the scene (can be updated and drawn)
    bool isActive = true;

public:
    // Constructor: Initializes a new node with default values
    Node();

    // Destructor: Cleans up the node and its resources
    virtual ~Node();

    // Retrieves the Transform object associated with this node
    Transform* getTransform();

    // Sets whether the node is active or not
    void setIsActive(bool active);

    // Gets the current activation status of the node
    bool getIsActive();

    // Updates the node (can be overridden by derived classes for custom update logic)
    virtual void update(float deltaTime);

    // Draws the node (can be overridden by derived classes for custom drawing logic)
    virtual void draw();

    // Adds a child node to this node's list of children
    void addChild(Node* child);

    // Retrieves the global position of this node, taking into account the entire transformation hierarchy
    Vector3 getGlobalPosition() const;
};
