#pragma once
#include "Scene.h"
#include "Character.h"
class FightingGameScene : public Scene
{
private:
    PlayerInput* player1Controller;
    PlayerInput* player2Controller;
    Character* character1;
    Character* character2;
    float leftBoundary;
    float rightBoundary;
public:
    FightingGameScene(Camera* cam, Renderer& rend, GameWindow& wind);
    ~FightingGameScene();
    void update(float deltaTime) override;
    void assignObjects() override;
    void handleCollision() override;
};

