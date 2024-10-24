#pragma once
#include "Square.h"
#include <map>

enum class AnimationState { Idle, WalkFront, WalkBack,cMK };

class AnimatedSquare : public Square
{
protected:
	struct Animation
	{
		int animIndex;
		int frameCount = 0.2;
		float frameDuration;
	};

	AnimationState currentState = AnimationState::Idle;
	std::map<AnimationState, Animation> animations;
	int frameCount = 5;
	float frameDuration = 0.2f; // Duration of each frame in seconds
	int currentFrame = 0;
	float elapsedTime = 0.0f;
	float frameWidth;
	float frameHeight;
	int animIndex = 0;


public:
	AnimatedSquare(Vector3 color, float alpha, Shader* shaderProgram);
	void set_animation(AnimationState newState);
	void update_animation(float deltaTime);
	bool isAnimationFinished() const;
	void draw() override;
};

