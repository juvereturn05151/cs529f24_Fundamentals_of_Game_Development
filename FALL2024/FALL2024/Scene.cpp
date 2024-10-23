#include "Scene.h"
#include "ObjectMesh.h"
#include "Triangle.h"
#include "Square.h"

#include "RotatingObject.h"

// Constructor initializes camera and renderer
Scene::Scene(Camera* cam, Renderer& rend, GameWindow& wind) : camera(cam), renderer(rend), window(wind) {}

void Scene::assignObjects()
{
    player1Controller = new PlayerInput(0, KeyboardMouse, window);
    player2Controller = new PlayerInput(1, KeyboardMouse, window);

    //Player 1
    AnimatedSquare* ryu = new AnimatedSquare(Vector3(0.0f, 0.0f, 1.0f), 0.5f, renderer.GetShader());
    ryu->AddTexture();
    Node* visualHolder = new ObjectMesh(ryu, renderer.GetModelMatrixLoc());
    visualHolder->getTransform()->setScale(Vector3(3.5f, 3.5f, 3.5f));
    visualHolder->getTransform()->setPosition(Vector3(-0.5f, 0.0f, 0.0f));

    character1 = new Character(NULL, renderer.GetModelMatrixLoc());
    character1->SetAnimatedSquare(ryu);
    character1->SetFaceRight(true);
    character1->addChild(visualHolder);

    animatedSquares.push_back(ryu);
    addObject(character1);

    AnimatedSquare* ryu2 = new AnimatedSquare(Vector3(0.0f, 0.0f, 1.0f), 0.5f, renderer.GetShader());
    ryu2->AddTexture();
    Node* visualHolder2 = new ObjectMesh(ryu2, renderer.GetModelMatrixLoc());
    visualHolder2->getTransform()->setScale(Vector3(-3.5f, 3.5f, 3.5f));
    visualHolder2->getTransform()->setPosition(Vector3(-0.5f, 0.0f, 0.0f));
    
    character2 = new Character(NULL, renderer.GetModelMatrixLoc());
    character2->SetAnimatedSquare(ryu2);
    character2->addChild(visualHolder2);

    animatedSquares.push_back(ryu2);
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

    for (AnimatedSquare* obj : animatedSquares)
    {
        //obj->getTransform()->setRotation(Vector3(0.0f, angle, 0.0f));
        obj->update_animation(deltaTime);  // Assuming objects have an update method
    }
    

    for (Node* obj : objects) 
    {
        //obj->getTransform()->setRotation(Vector3(0.0f, angle, 0.0f));
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

    for (AnimatedSquare* obj : animatedSquares)
    {
        obj->cleanup();
        delete obj;
    }

    for (Node* obj : objects) 
    {
        delete obj;
    }

    delete player1Controller;
    delete player2Controller;
}