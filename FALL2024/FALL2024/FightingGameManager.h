#pragma once
#include "GameManager.h"
class FightingGameManager : public GameManager
{
public:
    // Override the initialize method
    void initialize() override;

    // Override the update method
    void update() override;

    // Override the reset method
    void reset() override;

};

