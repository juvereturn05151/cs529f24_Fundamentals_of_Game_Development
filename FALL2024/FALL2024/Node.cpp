#include "Node.h"

Node::Node()
{
    transform = new Transform();
}

Node::~Node()
{

}

void Node::update(float deltaTime)
{
    for (Node* child : children)
    {
        child->update(deltaTime);
    }
}

void Node::draw()
{

}

Transform* Node::getTransform()
{
    return transform;
}

void Node::addChild(Node* child)
{
    children.push_back(child);
}