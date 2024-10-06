#include <iostream>
#include "GameWindow.h"
#include "Renderer.h"

int main() 
{
    try {
        GameWindow window(800, 600, "OpenGL Window");
        Renderer renderer(window);

        while (!window.shouldClose()) {
            window.pollEvents();

            renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

            // Render your 3D scene here
            renderer.updateCamera();
            renderer.draw();
            renderer.swapBuffers();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;

}
