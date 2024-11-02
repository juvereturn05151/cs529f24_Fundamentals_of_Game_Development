#pragma once
#include "Character.h"
class FightingGameManager
{
private:
    // Private constructor for singleton
    Character* character1;
    Character* character2;
    Vector3 startingPos1;
    Vector3 startingPos2;

    //Reset
    bool hasReset;
    const float countDownToReset = 3.0f;
    float currentCountDownToReset = 0.0f;

    // Private constructor and destructor to prevent instantiation
    FightingGameManager() : character1(nullptr), character2(nullptr) {}
    ~FightingGameManager() {}

    // Delete copy constructor and assignment operator to prevent copying
    FightingGameManager(const FightingGameManager&) = delete;
    FightingGameManager& operator=(const FightingGameManager&) = delete;

public:
    static FightingGameManager& getInstance()
    {
        static FightingGameManager instance;
        return instance;
    }

    void initialize(Character* _character1, Character* _character2);

    // Override the update method
    void update(float deltaTime);

    // Override the reset method
    void reset();

};

