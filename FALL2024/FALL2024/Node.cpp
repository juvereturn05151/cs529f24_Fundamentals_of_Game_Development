#include "Node.h"

// Constructor
Node::Node()
    : transform(new Transform()), parent(nullptr), isActive(true)
{
}

// Destructor
Node::~Node()
{
    delete transform;
}

// Update function to recursively update all child nodes
void Node::update(float deltaTime)
{
    for (Node* child : children)
    {
        child->update(deltaTime);
    }
}

// Draw function to recursively draw all child nodes if this node is active
void Node::draw()
{
    if (isActive)
    {
        for (Node* child : children)
        {
            child->draw();
        }
    }
}

// Get the transform of this node
Transform* Node::getTransform()
{
    return transform;
}

// Compute the global model matrix by combining this node's transform with its parent's
Matrix4<float> Node::getGlobalModelMatrix() const
{
    Matrix4<float> localModelMatrix = transform->getModelMatrix();

    if (parent)
    {
        return localModelMatrix * parent->getGlobalModelMatrix();
    }

    return localModelMatrix;
}

// Set the parent of this node
void Node::setParent(Node* newParent)
{
    parent = newParent;
}

// Add a child node and set this node as its parent
void Node::addChild(Node* child)
{
    child->setParent(this);
    children.push_back(child);
}

// Get the global position of this node by adding its local position to the parent's global position
Vector3 Node::getGlobalPosition() const
{
    if (parent && parent->getTransform())
    {
        return parent->getGlobalPosition() + transform->getPosition();
    }

    return transform->getPosition();
}

// Set the active state of this node
void Node::setIsActive(bool active)
{
    isActive = active;
}

// Get the active state of this node
bool Node::getIsActive()
{
    return isActive;
}