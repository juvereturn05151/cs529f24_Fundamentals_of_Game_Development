#pragma once
#include "Node.h" 
#include "Renderer.h" 
class Canvas
{
protected:
    Renderer& renderer;
	std::vector<Node*> userInterfaces;
    void addObject(Node* obj);
public:
    Canvas(Renderer& rend);

    // Render all objects in the scene
    void draw();

    // Update the scene (e.g., for animations or physics)
    virtual void update(float deltaTime);

    // Destructor to clean up dynamically allocated objects
    virtual ~Canvas();
};

