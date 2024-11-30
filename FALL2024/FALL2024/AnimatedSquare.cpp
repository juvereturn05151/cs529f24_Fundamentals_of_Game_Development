#include "AnimatedSquare.h"
#include "FrameController.h"

// Constructor initializing animations and default state
AnimatedSquare::AnimatedSquare(float frameWidth, float frameHeight
    ,const Vector3& color, float alpha, Shader* shaderProgram)
    : frameWidth(frameWidth), frameHeight(frameHeight), Square(color, alpha, shaderProgram)
{
    
}

AnimatedSquare::AnimatedSquare(const Vector3& point1, const Vector3& point2, const Vector3& point3, const Vector3& point4, 
    float frameWidth, float frameHeight, const Vector3& color, float alpha, Shader* shaderProgram)
    : frameWidth(frameWidth), frameHeight(frameHeight), Square(point1, point2, point3, point4, color, alpha, shaderProgram)
{

}

// Update animation frame based on elapsed time
void AnimatedSquare::updateAnimation(float deltaTime) 
{
    elapsedTime += deltaTime;
    if (elapsedTime >= frameDuration) 
    {
        if (isLoop) 
        {
            currentFrame = (currentFrame + 1) % frameCount; // Loop frames
        }
        else if (currentFrame < frameCount - 2) 
        {
            currentFrame++; // Advance without looping
        }
        elapsedTime -= frameDuration;
    }

    updateVertices();
}

// Helper function to update vertex UV coordinates
void AnimatedSquare::updateVertices() 
{
    float left = currentFrame * frameWidth;
    float right = left + frameWidth;
    float top = 1.0f - (frameHeight * animIndex);
    float bottom = top - frameHeight;

    vertices = 
    {
        squareVertices[0], squareVertices[1], squareVertices[2], color.x, color.y, color.z, alpha, left, bottom,
        squareVertices[3], squareVertices[4], squareVertices[5], color.x, color.y, color.z, alpha, left, top,
        squareVertices[6], squareVertices[7], squareVertices[8], color.x, color.y, color.z, alpha, right, top,
        squareVertices[9], squareVertices[10], squareVertices[11], color.x, color.y, color.z, alpha, right, bottom
    };

    indices = { 0, 1, 2, 0, 3, 2 };
    editBuffers();
}

// Check if the animation has finished
bool AnimatedSquare::isAnimationFinished() const 
{
    return currentFrame == (frameCount - 1);
}

// Check if the animation is at a specific frame
bool AnimatedSquare::isAtFrame(int frameNumber) const 
{
    return currentFrame == (frameNumber - 1);
}

// Draw the animated square
void AnimatedSquare::draw() 
{
    Square::draw();
}