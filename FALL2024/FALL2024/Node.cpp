#include "Node.h"

Node::Node()
{

}

Node::~Node()
{

}

void Node::update()
{
    for (Node* child : children)
    {
        child->update();
    }
}

Transform Node::getTransform()
{
    return transform;
}

void Node::addChild(Node* child)
{
    children.push_back(child);
}