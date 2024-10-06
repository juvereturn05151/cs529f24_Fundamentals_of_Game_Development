#include "Scene.h"

// Constructor initializes camera and renderer
Scene::Scene(Camera* cam, Renderer* rend)
    : camera(cam), renderer(rend) {}

// Add objects to the scene
void Scene::addObject(Node* obj) {
    objects.push_back(obj);
}

// Update objects in the scene (animations, physics, etc.)
void Scene::update(float deltaTime) {
    for (Node* obj : objects) {
        obj->update(deltaTime);  // Assuming objects have an update method
    }
}

// Render the scene
void Scene::draw() {
    // First, clear the screen
    renderer->clear(0.2f, 0.3f, 0.3f, 1.0f);

    // Get the camera's view and projection matrices
    /*Matrix4 viewMatrix = camera->getViewMatrix();
    Matrix4 projectionMatrix = camera->getProjectionMatrix();*/

    // Render all objects
    for (Node* obj : objects) 
    {
        obj->draw();
    }

    // Swap buffers after rendering
    renderer->swapBuffers();
}

// Set the camera
void Scene::setCamera(Camera* cam) {
    camera = cam;
}

// Destructor to clean up dynamically allocated memory
Scene::~Scene() {
    for (Node* obj : objects) 
    {
        delete obj;
    }
}