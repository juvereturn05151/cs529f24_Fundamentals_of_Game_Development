#include "FightingGameManager.h"
#include "EventSystem.h"
#include "SoundManager.h"

// Override the initialize method
void FightingGameManager::initialize(Character* _character1, Character* _character2) 
{
	character1 = _character1;
	character2 = _character2;
	startingPos1 = _character1->getTransform()->getPosition();
	startingPos2 = _character2->getTransform()->getPosition();
}

// Override the update method
void FightingGameManager::update(float deltaTime)
{
	if (currentGameState == GameState::ReadyFight) 
	{
		messageTimer += deltaTime;
		if (messageTimer < readyDuration)
		{
			// Display "Ready" message
			if (!hasPlayReadySound)
			{
				SoundManager::getInstance().playSound("audio/ready-101soundboards.mp3", false);
				hasPlayReadySound = true;
			}


			EventSystem::getInstance().notify("triggerReadyUI");
		}
		else if (messageTimer < readyDuration + fightDuration)
		{
			// Display "Fight" message
			if (!hasPlayFightSound) 
			{
				SoundManager::getInstance().playSound("audio/fight-101soundboards.mp3", false);
				hasPlayFightSound = true;
			}

			EventSystem::getInstance().notify("triggerFightUI");
		}
		else
		{
			// Transition to the actual fight
			EventSystem::getInstance().notify("disableReadyAndFightUI");
			currentGameState = GameState::InSession;
			messageTimer = 0.0f;
			hasPlayFightSound = false;
			hasPlayReadySound = false;
			character1->setIsReadyToFight(true);
			character2->setIsReadyToFight(true);
		}
	}
	else if (currentGameState == GameState::InSession)
	{
		if (character1 != NULL && character2 != NULL)
		{
			if (character1->getYouWin() || character2->getYouWin())
			{
				currentGameState = GameState::AfterMath;
			}
		}
	}
	else  if (currentGameState == GameState::AfterMath)
	{
		currentCountDownToReset += deltaTime;
		if (currentCountDownToReset >= countDownToReset)
		{
			if (!hasReset)
			{
				hasReset = true;
				reset();
			}
		}
	}
}

// Override the reset method
void FightingGameManager::reset() 
{
	if (character1->getHealth() <= 0 || character2->getHealth() <= 0) 
	{
		return;
	}

	character1->getTransform()->setPosition(startingPos1);
	character2->getTransform()->setPosition(startingPos2);
	character1->reset();
	character2->reset();
	currentCountDownToReset = 0;
	hasReset = false;
	currentGameState = GameState::ReadyFight;
}

void FightingGameManager::setGameState(GameState newGameState)
{
	currentGameState = newGameState;
}

GameState FightingGameManager::getGameState()
{
	return currentGameState;
}