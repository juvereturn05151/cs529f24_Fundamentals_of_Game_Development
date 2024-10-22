#include "FrameController.h"
#include <glfw/glfw3.h>
// Initialize the singleton instance
FrameController& FrameController::getInstance()
{
    static FrameController instance;
    return instance;
}

// Private constructor to initialize time variables
FrameController::FrameController()
    : deltaTime(0.0f), fps(0.0f)
{
    lastFrameTime = std::chrono::high_resolution_clock::now();
    currentTime = 0.0f;
    lastTime = 0.0f;
}

// Update the time difference between frames
void FrameController::update()
{
    currentTime = glfwGetTime(); // Using GLFW's time function (or any other time function you're using)
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
}

// Return the delta time
float FrameController::getDeltaTime() const
{
    return deltaTime;
}

// Return the calculated FPS
float FrameController::getFPS() const
{
    return fps;
}

void FrameController::setTimeScale(float scale)
{
    timeScale = scale;
}

float FrameController::getTimeScale() const
{
    return timeScale;
}