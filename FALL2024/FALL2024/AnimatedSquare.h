#pragma once
#include "Square.h"
class AnimatedSquare : public Square
{
protected:
	float startingOffsetX;
	float offsetXIncrement;
	int frameCount = 4;
	float frameDuration = 0.2f; // Duration of each frame in seconds
	int currentFrame = 0;
	float elapsedTime = 0.0f;
	float frameWidth;

public:
	AnimatedSquare(Vector3 color, float alpha, Shader* shaderProgram);
	void update_animation(float deltaTime);
	void draw() override;
};

