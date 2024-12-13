/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Brief: a specialized version of Square that supports frame-based animations.
*/

#pragma once

#include "Square.h" // Base class header file
#include <map>       // Standard library header for std::map

// AnimatedSquare: A class for handling animations in a square object, using frame-based animation logic.
class AnimatedSquare : public Square {
protected:
    // Animation struct to store animation metadata.
    struct Animation {
        int animIndex;       // Identifier for the animation sequence
        int frameCount;      // Total number of frames in the animation
        float frameDuration; // Duration of each frame in seconds
    };

    // Animation-related properties
    int frameCount = 5;        // Number of frames in the current animation
    float frameDuration = 0.2f; // Duration of each frame (in seconds)
    int currentFrame = 0;      // Index of the current frame being displayed
    float elapsedTime = 0.0f;  // Accumulated time since the last frame update

    // Frame dimensions
    float frameWidth = 0.1f;   // Width of a single frame (normalized units)
    float frameHeight = 0.1f;  // Height of a single frame (normalized units)

    // Animation control
    int animIndex = 0;         // Index of the active animation
    bool isLoop = true;        // Indicates if the animation should loop

    // Updates the vertices of the square to match the current frame.
    void updateVertices();

public:
    // Constructors
    // Initializes an AnimatedSquare with uniform frame dimensions and a single color.
    AnimatedSquare(float frameWidth, float frameHeight, const Vector3& color, float alpha, Shader* shaderProgram);

    // Initializes an AnimatedSquare with custom vertices, frame dimensions, and color.
    AnimatedSquare(const Vector3& point1, const Vector3& point2, const Vector3& point3, const Vector3& point4, 
        float frameWidth, float frameHeight, const Vector3& color, float alpha, Shader* shaderProgram);

    // Updates the animation state based on the elapsed time since the last update.
    void updateAnimation(float deltaTime);

    // Returns true if the animation has finished (non-looping animations only).
    bool isAnimationFinished() const;

    // Returns true if the animation is currently at the specified frame.
    bool isAtFrame(int frameNumber) const;

    // Overrides the draw method to ensure the correct frame is displayed.
    void draw() override;
};
