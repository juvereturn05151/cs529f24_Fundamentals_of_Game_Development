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
#include "Vector3.h"
#include "Shader.h"

class Renderer
{
private:
	GameWindow &game_window;
	Shader* shader;
	GLuint VAO, VBO, EBO;

public:
	Renderer(GameWindow &game_window);
	~Renderer();
	void clear(float r, float g, float b, float a);
	void swapBuffers();
	void drawTriangle(Vector3 point1, Vector3 point2, Vector3 point3);

private:
	bool initializeLibraries();
	bool loadGraphicsAPIFunctions();
	void setupCallbacks();
	void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	void shutdownLibraries();
	void initShader();
};