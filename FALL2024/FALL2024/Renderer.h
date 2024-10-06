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
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "ObjectMesh.h"

class Renderer
{
private:
	GameWindow &game_window;
	Shader* shader;
	float angle;
	Camera *camera;
	ObjectMesh* objectMesh;
	ObjectMesh* objectMesh2;
	GLint modelMatrixLoc;

public:
	Renderer(GameWindow &game_window);
	~Renderer();
	void clear(float r, float g, float b, float a);
	void swapBuffers();
	void draw();
	void setColor(Vector3 color, float alpha);
	void updateCamera();

private:
	bool initializeLibraries();
	bool loadGraphicsAPIFunctions();
	void setupCallbacks();
	void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	void shutdownLibraries();
	void initShader();

};