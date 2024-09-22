#include "GameWindow.h"

GameWindow::GameWindow(int width, int height, const char* name)
{
	this->width = width;
	this->height = height;
	window_name = name;
}

GameWindow::~GameWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* GameWindow::createWindow() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(getWidth(), getHeight(), getWindowName(), NULL, NULL);

	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		return nullptr;
	}

	return window;
}

void GameWindow::pollEvents() 
{
	glfwPollEvents();
}

bool GameWindow::shouldClose()
{
	if (window == nullptr) 
	{
		return false;
	}

	return glfwWindowShouldClose(window);
}

int GameWindow::getWidth() 
{
	return width;
}

int GameWindow::getHeight() 
{
	return height;
}

const char* GameWindow::getWindowName() 
{
	return window_name;
}

void GameWindow::setWindow(GLFWwindow* window) 
{
	this->window = window;
}

GLFWwindow* GameWindow::getWindow() 
{
	return this->window;
}