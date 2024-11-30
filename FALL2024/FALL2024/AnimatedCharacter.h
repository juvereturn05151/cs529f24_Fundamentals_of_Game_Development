#pragma once
#include "AnimatedSquare.h"

enum class AnimationState { Idle, WalkFront, WalkBack, cMK, Hurt, Hadoken, YouWin, YouLose, Block, Throw };

class AnimatedCharacter : public AnimatedSquare
{
protected:
	AnimationState currentState = AnimationState::Idle;
	std::map<AnimationState, Animation> animations;
	void Initialize();

public:
	AnimatedCharacter(float frameWidth, float frameHeight, const Vector3& color, float alpha, Shader* shaderProgram);
	AnimatedCharacter(const Vector3& point1, const Vector3& point2, const Vector3& point3, const Vector3& point4, 
		float frameWidth, float frameHeight, const Vector3& color, float alpha, Shader* shaderProgram);
	void setAnimation(AnimationState newState, bool isLoop = true);
	AnimationState getCurrentState() const;
};

