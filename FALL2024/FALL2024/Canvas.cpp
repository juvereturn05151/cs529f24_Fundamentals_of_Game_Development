#include "Canvas.h"

Canvas::Canvas() 
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