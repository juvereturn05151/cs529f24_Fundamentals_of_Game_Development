#include "Scene.h"
#include "ObjectMesh.h"

// Constructor initializes camera and renderer
Scene::Scene(Camera* cam, Renderer& rend) : camera(cam), renderer(rend) {}

void Scene::AssignObjects()
{
    Mesh* mesh = new Mesh(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), 0.1f);
    ObjectMesh * objectMesh = new ObjectMesh(mesh, renderer.GetModelMatrixLoc());
    objectMesh->getTransform()->setPosition(Vector3(0.0f, 2.0f, 0.0f));
    objectMesh->getTransform()->setScale(Vector3(2.0f, 2.0f, 2.0f));

    addObject(objectMesh);

    Mesh* mesh2 = new Mesh(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), 0.5f);
    ObjectMesh * objectMesh2 = new ObjectMesh(mesh2, renderer.GetModelMatrixLoc());
    objectMesh2->getTransform()->setPosition(Vector3(3.0f, 1.0f, -2.0f));  // Different position from object1
    objectMesh2->getTransform()->setScale(Vector3(1.0f, 1.0f, 1.0f));

    addObject(objectMesh2);
}

// Add objects to the scene
void Scene::addObject(Node* obj) 
{
    objects.push_back(obj);
}

// Update objects in the scene (animations, physics, etc.)
void Scene::update(float deltaTime) {
    angle += 0.05f * 0.05f;
    for (Node* obj : objects) 
    {
        obj->getTransform()->setRotation(Vector3(0.0f, angle, 0.0f));
        obj->update(deltaTime);  // Assuming objects have an update method
    }
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

    // Swap buffers after rendering
    renderer.swapBuffers();
}

// Destructor to clean up dynamically allocated memory
Scene::~Scene() {
    for (Node* obj : objects) 
    {
        delete obj;
    }
}