#pragma once

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include <iostream>

#include "GameWindow.h"

class Renderer
{
private:
	GameWindow &game_window;

public:
	Renderer(GameWindow &game_window);
	void clear(float r, float g, float b, float a);
	void swapBuffers();

private:
	bool initializeLibraries();
	bool setupGraphicsContext(GLFWwindow* window);
	bool loadGraphicsAPIFunctions();
	void shutdownWindow(GLFWwindow* window);
	void shutdownLibraries();
};