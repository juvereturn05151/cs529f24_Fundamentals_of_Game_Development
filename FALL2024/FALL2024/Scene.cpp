#include "Scene.h"
#include "ObjectMesh.h"
#include "Triangle.h"
#include "Square.h"
#include "BoxCollider2D.h"
#include "RotatingObject.h"

// Constructor initializes camera and renderer
Scene::Scene(Camera* cam, Renderer& rend, GameWindow& wind) : camera(cam), renderer(rend), window(wind) {}

void Scene::assignObjects()
{
    player1Controller = new PlayerInput(0, KeyboardMouse, window);
    player2Controller = new PlayerInput(1, KeyboardMouse, window);

    character1 = new Character(NULL, renderer.GetModelMatrixLoc(), renderer, 0);
    character1->SetFaceRight(true);
    addObject(character1);

    character2 = new Character(NULL, renderer.GetModelMatrixLoc(), renderer, 1);
    addObject(character2);
}

// Add objects to the scene
void Scene::addObject(Node* obj) 
{
    objects.push_back(obj);
}

// Update objects in the scene (animations, physics, etc.)
void Scene::update(float deltaTime) {
    if (player1Controller) {
        player1Controller->Update();
        character1->updateInput(player1Controller);

    }
    if (player2Controller) {
        player2Controller->Update();
        character2->updateInput(player2Controller);
    }

    for (Node* obj : objects) 
    {
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
Scene::~Scene() 
{
    for (Node* obj : objects) 
    {
        delete obj;
    }

    if (player1Controller != NULL)
    {
        delete player1Controller;
    }

    if (player2Controller != NULL)
    {
        delete player2Controller;
    }
}