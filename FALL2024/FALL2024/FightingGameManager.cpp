#include "FightingGameManager.h"

// Override the initialize method
void FightingGameManager::initialize(Character* _character1, Character* _character2) 
{
	character1 = _character1;
	character2 = _character2;
	startingPos1 = _character1->getTransform()->getPosition();
	startingPos2 = _character2->getTransform()->getPosition();
}

// Override the update method
void FightingGameManager::update() 
{
	if (character1 != NULL && character2 != NULL) 
	{
		if (character1->getYouWin() || character2->getYouWin()) 
		{
			reset();
		}
	}
}

// Override the reset method
void FightingGameManager::reset() 
{
	character1->getTransform()->setPosition(startingPos1);
	character2->getTransform()->setPosition(startingPos2);
}