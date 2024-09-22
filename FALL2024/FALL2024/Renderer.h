#pragma once

/*
	Auther: Ju-ve Chankasemporn
	E-mail: juvereturn@gmail.com
	Brief: Initialize graphic library, clear the screen, and swap the buffer
*/

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
	bool loadGraphicsAPIFunctions();
	void shutdownLibraries();
};