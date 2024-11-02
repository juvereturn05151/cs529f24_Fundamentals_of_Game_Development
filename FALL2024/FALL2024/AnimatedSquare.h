#pragma once

#include "Square.h"
#include <map>

enum class AnimationState { Idle, WalkFront, WalkBack, cMK, Hurt, Hadoken, YouWin, YouLose, Block };

class AnimatedSquare : public Square {
protected:
    struct Animation
    {
        int animIndex;
        int frameCount;
        float frameDuration;
    };

    AnimationState currentState = AnimationState::Idle;
    std::map<AnimationState, Animation> animations;
    int frameCount = 5;
    float frameDuration = 0.2f;
    int currentFrame = 0;
    float elapsedTime = 0.0f;
    float frameWidth = 0.1f;
    float frameHeight = 0.1f;
    int animIndex = 0;
    bool isLoop = true;

    void updateVertices();

public:
    AnimatedSquare(const Vector3& color, float alpha, Shader* shaderProgram);
    void setAnimation(AnimationState newState, bool isLoop = true);
    void updateAnimation(float deltaTime);
    bool isAnimationFinished() const;
    bool isAtFrame(int frameNumber) const;
    void draw() override;
    AnimationState getCurrentState() const;
};