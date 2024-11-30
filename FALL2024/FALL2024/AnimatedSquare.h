#pragma once

#include "Square.h"
#include <map>

class AnimatedSquare : public Square {
protected:
    struct Animation
    {
        int animIndex;
        int frameCount;
        float frameDuration;
    };

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
    AnimatedSquare(float frameWidth, float frameHeight, const Vector3& color, float alpha, Shader* shaderProgram);
    AnimatedSquare(const Vector3& point1, const Vector3& point2, const Vector3& point3, const Vector3& point4, float frameWidth, float frameHeight, const Vector3& color, float alpha, Shader* shaderProgram);
    void updateAnimation(float deltaTime);
    bool isAnimationFinished() const;
    bool isAtFrame(int frameNumber) const;
    void draw() override;

};