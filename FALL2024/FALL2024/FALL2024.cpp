#include <iostream>
#include "GameWindow.h"
#include "Renderer.h"
#include "Camera.h"
#include "FightingGameScene.h"
#include "FrameController.h"
#include "InputManager.h"

int main() 
{
    try 
    {
        GameWindow window(1920, 1080, "OpenGL Window");
        Renderer renderer(window);
        //printf("Rendered by: %s\n", glGetString(GL_RENDERER));
        Camera * camera = new Camera(renderer.GetViewMatrixLoc(), renderer.GetProjectionMatrixLoc(), window);
        InputManager::Initialize(window.getWindow());
        Scene * scene = new FightingGameScene(camera,renderer, window);

        scene->assignObjects();

        while (!window.shouldClose()) 
        {
            window.pollEvents();

            FrameController::getInstance().update();

            scene->update(FrameController::getInstance().getDeltaTime());
            scene->draw();

            InputManager::Update();
        }

        delete camera;
        delete scene;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;

}
