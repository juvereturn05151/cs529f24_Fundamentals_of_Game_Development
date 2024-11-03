#pragma once
#include "Node.h" 

class Canvas
{
protected:
	std::vector<Node*> objects;
public:
    Canvas();

    // Render all objects in the scene
    void draw();

    // Update the scene (e.g., for animations or physics)
    virtual void update(float deltaTime);

    // Destructor to clean up dynamically allocated objects
    virtual ~Canvas();
};

