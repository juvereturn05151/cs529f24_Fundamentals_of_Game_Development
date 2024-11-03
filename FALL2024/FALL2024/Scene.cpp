#include "Scene.h"
#include "GameObject.h"
#include "Triangle.h"
#include "Square.h"
#include "BoxCollider2D.h"

// Constructor initializes camera and renderer
Scene::Scene(Camera* cam, Renderer& rend, GameWindow& wind) : camera(cam), renderer(rend), window(wind) 
{

}

void Scene::assignObjects()
{

}

// Add objects to the scene
void Scene::addObject(Node* obj) 
{
    objects.push_back(obj);
}

// Update objects in the scene (animations, physics, etc.)
void Scene::update(float deltaTime) 
{
    for (Node* obj : objects) 
    {
        obj->update(deltaTime);  // Assuming objects have an update method
    }

    if (canvas != NULL)
    {
        canvas->update(deltaTime);
    }
}

void Scene::handleCollision()
{
    
}

// Render the scene
void Scene::draw() {
    // First, clear the screen
    renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

    // Get the camera's view and projection matrices
    camera->updateCamera();

    // Render all objects
    for (Node* obj : objects) 
    {
        obj->draw();
    }

    if (canvas != NULL)
    {
        canvas->draw();
    }

    // Swap buffers after rendering
    renderer.swapBuffers();
}

// Destructor to clean up dynamically allocated memory
Scene::~Scene() 
{
    for (Node* obj : objects) 
    {
        delete obj;
    }

    if (canvas != NULL) 
    {
        delete canvas;
    }
}