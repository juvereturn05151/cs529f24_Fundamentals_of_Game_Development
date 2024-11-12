#pragma once
#include "AnimatedSquare.h"

enum class AnimationState { Idle, WalkFront, WalkBack, cMK, Hurt, Hadoken, YouWin, YouLose, Block, Throw };

class AnimatedCharacter : public AnimatedSquare
{
protected:
	AnimationState currentState = AnimationState::Idle;
	std::map<AnimationState, Animation> animations;

public:
	AnimatedCharacter(const Vector3& color, float alpha, Shader* shaderProgram);
	void setAnimation(AnimationState newState, bool isLoop = true);
	AnimationState getCurrentState() const;
};

