#include <iostream>
#include <irrKlang.h>
#include "GameWindow.h"
#include "Renderer.h"
#include "Camera.h"
#include "FightingGameScene.h"
#include "FrameController.h"
#include "InputManager.h"
using namespace irrklang;

int main() 
{
    try 
    {
        ISoundEngine* engine = createIrrKlangDevice();
        if (!engine) 
        {
            return 0;
        }
        engine->play2D("audio/Street Fighter Alpha Ryu Theme.mp3", true);


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
        engine->drop();
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
