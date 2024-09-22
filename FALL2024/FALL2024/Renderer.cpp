#include "Renderer.h"

Renderer::Renderer(GameWindow &game_window) : game_window(game_window)
{
    if (!initializeLibraries()) 
    {
        return;
    }

    GLFWwindow* window = game_window.createWindow();
    if (!window) 
    {
        shutdownLibraries();
        return;
    }

    if (!setupGraphicsContext(window)) 
    {
        shutdownWindow(window);
        shutdownLibraries();
        return;
    }

    if (!loadGraphicsAPIFunctions()) 
    {
        shutdownWindow(window);
        shutdownLibraries();
        return;
    }

    this->game_window = game_window;
}


void Renderer::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::swapBuffers()
{
    if (game_window.getWindow() != nullptr)
    {
        glfwSwapBuffers(game_window.getWindow());
    }
}

bool Renderer::initializeLibraries() {
    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    return true;
}

bool Renderer::setupGraphicsContext(GLFWwindow* window) 
{
    glfwMakeContextCurrent(window);
    return true;
}

bool Renderer::loadGraphicsAPIFunctions() 
{
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    return true;
}

void updateWindow(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void Renderer::shutdownLibraries()
{
    glfwTerminate();
}

void Renderer::shutdownWindow(GLFWwindow* window)
{
    glfwDestroyWindow(window);
}
