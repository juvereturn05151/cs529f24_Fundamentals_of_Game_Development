#pragma once
#include <vector>
#include "Camera.h"
#include "Renderer.h"
#include "Node.h" 
#include "GameWindow.h"

class Scene {
protected:
    std::vector<Node*> objects;  // List of objects in the scene
    Camera* camera;                // Pointer to the camera
    Renderer& renderer;            // Pointer to the renderer
    GameWindow& window;

public:
    // Constructor
    Scene(Camera* cam, Renderer& rend, GameWindow& wind);

    virtual void assignObjects();

    virtual void handleCollision();

    // Add objects to the scene
    void addObject(Node* obj);

    // Render all objects in the scene
    void draw();

    // Update the scene (e.g., for animations or physics)
    virtual void update(float deltaTime);

    // Destructor to clean up dynamically allocated objects
    virtual ~Scene();
};
