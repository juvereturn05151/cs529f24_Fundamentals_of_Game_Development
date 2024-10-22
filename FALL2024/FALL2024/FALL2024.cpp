#include <iostream>
#include "GameWindow.h"
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
#include "FrameController.h"

int main() 
{
    try {
        GameWindow window(800, 600, "OpenGL Window");
        Renderer renderer(window);
        Camera * camera = new Camera(renderer.GetViewMatrixLoc(), renderer.GetProjectionMatrixLoc(), window);
        Scene * scene = new Scene(camera,renderer);

        scene->assignObjects();

        while (!window.shouldClose()) {
            window.pollEvents();

            FrameController::getInstance().update();

            scene->update(FrameController::getInstance().getDeltaTime());
            scene->draw();
        }

        delete camera;
        delete scene;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;

}
