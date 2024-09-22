#pragma once

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include <iostream>

class GameWindow
{
private:
	int width;
	int height;
	const char* window_name;
	GLFWwindow* window;

public:
	//Functions
	GameWindow(int width, int height, const char* name);
	~GameWindow();
	void pollEvents();
	bool shouldClose();
	GLFWwindow* createWindow();

	//Setter Getter
	GLFWwindow* getWindow();
};

