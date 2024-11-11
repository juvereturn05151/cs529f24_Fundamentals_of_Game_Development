#include "AnimatedSquare.h"
#include "FrameController.h"

// Constructor initializing animations and default state
AnimatedSquare::AnimatedSquare(const Vector3& color, float alpha, Shader* shaderProgram)
    : Square(color, alpha, shaderProgram)
{
    animations = 
    {
        { AnimationState::Idle,      {0, 5, 0.2f} },
        { AnimationState::WalkFront, {1, 6, 0.2f} },
        { AnimationState::WalkBack,  {2, 6, 0.2f} },
        { AnimationState::cMK,       {3, 7, 0.1f} },
        { AnimationState::Hurt,      {4, 4, 0.15f} },
        { AnimationState::Hadoken,   {6, 6, 0.2f} },
        { AnimationState::YouWin,    {7, 6, 0.2f} },
        { AnimationState::YouLose,   {5, 11, 0.2f} },
        { AnimationState::Block,     {9, 6, 0.2f} },
        { AnimationState::Throw,     {8, 6, 0.2f} }
    };

    setAnimation(AnimationState::Idle, true);
}

// Set animation state and reset frame-related parameters
void AnimatedSquare::setAnimation(AnimationState newState, bool isLoop) 
{
    if (currentState != newState) 
    {
        currentState = newState;
        currentFrame = 0;
        elapsedTime = 0.0f;
        animIndex = animations[currentState].animIndex;
        frameCount = animations[currentState].frameCount;
        frameDuration = animations[currentState].frameDuration;
        this->isLoop = isLoop;
    }
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

// Get the current animation state
AnimationState AnimatedSquare::getCurrentState() const
{
    return currentState;
}