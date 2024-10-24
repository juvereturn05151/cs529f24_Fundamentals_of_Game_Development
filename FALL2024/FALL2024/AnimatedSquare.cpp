#include "AnimatedSquare.h"
#include "FrameController.h"

AnimatedSquare::AnimatedSquare(Vector3 color, float alpha, Shader* shaderProgram) : Square(color, alpha, shaderProgram)
{
    animations[AnimationState::Idle] = {0, 5, 0.2f };
    animations[AnimationState::WalkFront] = {1, 6, 0.2f };
    animations[AnimationState::WalkBack] = {2, 6, 0.2f };
    animations[AnimationState::cMK] = { 3, 6, 0.125f };

    set_animation(AnimationState::Idle);

    frameWidth = 0.1f;
    frameHeight = 0.1f;
}

void AnimatedSquare::set_animation(AnimationState newState)
{
    if (currentState != newState) 
    {
        currentState = newState;
        currentFrame = 0; // Reset to the first frame
        elapsedTime = 0.0f; // Reset time tracking
        animIndex = animations[currentState].animIndex;
        frameCount = animations[currentState].frameCount;
        frameDuration = animations[currentState].frameDuration;
    }
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
    float top = 1.0f - (frameHeight * animIndex);  // Assuming the sprite is single-row, so top = 0
    float bottom = top - frameHeight;

    vertices =
    {
        squareVertices[0], squareVertices[1], squareVertices[2], color.x, color.y, color.z, alpha, left, bottom,
        squareVertices[3], squareVertices[4], squareVertices[5], color.x, color.y, color.z, alpha, left, top,
        squareVertices[6], squareVertices[7], squareVertices[8], color.x, color.y, color.z, alpha, right, top,
        squareVertices[9], squareVertices[10], squareVertices[11], color.x, color.y, color.z, alpha, right, bottom
    };

    indices =
    {
        0, 1, 2,  // Define the triangle using vertex indices
        0, 3, 2
    };

    editBUffers();
}

bool AnimatedSquare::isAnimationFinished() const
{
    // If the current frame is the last frame of the animation, return true
    return currentFrame == (frameCount - 1);
}

void AnimatedSquare::draw()
{
	Square::draw();
}