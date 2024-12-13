#include "AnimatedCharacter.h"

AnimatedCharacter::AnimatedCharacter(float frameWidth, float frameHeight,
    const Vector3& color, float alpha, Shader* shaderProgram)
    : AnimatedSquare(frameWidth, frameHeight, color, alpha, shaderProgram)
{
    Initialize();
}

AnimatedCharacter::AnimatedCharacter(const Vector3& point1, const Vector3& point2, const Vector3& point3, const Vector3& point4,
    float frameWidth, float frameHeight, const Vector3& color, float alpha, Shader* shaderProgram) 
    : AnimatedSquare(point1,point2, point3, point4, 
        frameWidth, frameHeight, color, alpha, shaderProgram)
{
    Initialize();
}

void AnimatedCharacter::Initialize()
{
    animations =
    {
        { AnimationState::Idle,      {0, 7, 0.2f} },
        { AnimationState::WalkFront, {1, 8, 0.1f} },
        { AnimationState::WalkBack,  {2, 8, 0.1f} },
        { AnimationState::cMK,       {3, 7, 0.15f} },
        { AnimationState::Hurt,      {4, 3, 0.15f} },
        { AnimationState::Hadoken,   {6, 8, 0.2f} },
        { AnimationState::YouWin,    {7, 6, 0.2f} },
        { AnimationState::YouLose,   {5, 13, 0.2f} },
        { AnimationState::Block,     {10, 6, 0.2f} },
        { AnimationState::Throw,     {9, 11, 0.2f} }
    };

    setAnimation(AnimationState::Idle, true);
}

// Set animation state and reset frame-related parameters
void AnimatedCharacter::setAnimation(AnimationState newState, bool isLoop)
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

// Get the current animation state
AnimationState AnimatedCharacter::getCurrentState() const
{
    return currentState;
}