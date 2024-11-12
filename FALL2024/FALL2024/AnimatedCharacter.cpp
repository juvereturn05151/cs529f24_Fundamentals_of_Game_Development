#include "AnimatedCharacter.h"

AnimatedCharacter::AnimatedCharacter(const Vector3& color, float alpha, Shader* shaderProgram)
    : AnimatedSquare(color, alpha, shaderProgram)
{
    animations =
    {
        { AnimationState::Idle,      {0, 5, 0.2f} },
        { AnimationState::WalkFront, {1, 6, 0.2f} },
        { AnimationState::WalkBack,  {2, 6, 0.2f} },
        { AnimationState::cMK,       {3, 7, 0.15f} },
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