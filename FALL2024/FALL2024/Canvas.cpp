#include "Canvas.h"

Canvas::Canvas(Renderer& rend): renderer(rend)
{

}

// Render all objects in the scene
void Canvas::draw()
{
    for (Node* obj : userInterfaces)
    {
        obj->draw();
    }
}

void Canvas::update(float deltaTime) 
{

}

// Destructor to clean up dynamically allocated objects
Canvas::~Canvas()
{
    for (Node* obj : userInterfaces)
    {
        if (obj != NULL)
        {
            delete obj;
        }
    }
}

void Canvas::addObject(Node* obj)
{
    userInterfaces.push_back(obj);
}