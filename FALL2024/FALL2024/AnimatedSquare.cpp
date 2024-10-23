#include "AnimatedSquare.h"
#include "FrameController.h"

AnimatedSquare::AnimatedSquare(Vector3 color, float alpha, Shader* shaderProgram) : Square(color, alpha, shaderProgram)
{
    frameWidth = 0.25f;
}

void AnimatedSquare::update_animation(float deltaTime)
{
    elapsedTime += deltaTime;
    if (elapsedTime >= frameDuration) 
    {
        currentFrame = (currentFrame + 1) % frameCount; // Cycle through frames
        elapsedTime -= frameDuration; // Reset elapsed time
    }

    float left = currentFrame * frameWidth;
    float right = left + frameWidth;
    float top = 0.0f;  // Assuming the sprite is single-row, so top = 0
    float bottom = 1.0f;

    vertices =
    {
        squareVertices[0], squareVertices[1], squareVertices[2], color.x, color.y, color.z, alpha, left, 0.0f,
        squareVertices[3], squareVertices[4], squareVertices[5], color.x, color.y, color.z, alpha, left, 1.0f,
        squareVertices[6], squareVertices[7], squareVertices[8], color.x, color.y, color.z, alpha, right, 1.0f,
        squareVertices[9], squareVertices[10], squareVertices[11], color.x, color.y, color.z, alpha, right, 0.0f
    };

    indices =
    {
        0, 1, 2,  // Define the triangle using vertex indices
        0, 3, 2
    };

    editBUffers();
}

void AnimatedSquare::draw()
{
	Square::draw();
}