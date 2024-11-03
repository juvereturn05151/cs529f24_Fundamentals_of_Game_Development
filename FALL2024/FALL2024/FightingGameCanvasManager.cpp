#include "FightingGameCanvasManager.h"
#include "EventSystem.h"

FightingGameCanvasManager::FightingGameCanvasManager(Renderer& rend) : Canvas(rend)
{
    HeartUI* heartUI1 = new HeartUI(NULL, renderer.GetModelMatrixLoc(), renderer, Vector3(-3.75f, 3.0f, 0.0f));
    player1HeartUI[0] = heartUI1;
    addObject(heartUI1);

    HeartUI* heartUI2 = new HeartUI(NULL, renderer.GetModelMatrixLoc(), renderer, Vector3(-4.75f, 3.0f, 0.0f));
    player1HeartUI[1] = heartUI2;
    addObject(heartUI2);

    HeartUI* heartUI3 = new HeartUI(NULL, renderer.GetModelMatrixLoc(), renderer, Vector3(-5.75f, 3.0f, 0.0f));
    player1HeartUI[2] = heartUI3;
    addObject(heartUI3);

    HeartUI* heartUI4 = new HeartUI(NULL, renderer.GetModelMatrixLoc(), renderer, Vector3(3.75f, 3.0f, 0.0f));
    player2HeartUI[0] = heartUI4;
    addObject(heartUI4);

    HeartUI* heartUI5 = new HeartUI(NULL, renderer.GetModelMatrixLoc(), renderer, Vector3(4.75f, 3.0f, 0.0f));
    player2HeartUI[1] = heartUI5;
    addObject(heartUI5);

    HeartUI* heartUI6 = new HeartUI(NULL, renderer.GetModelMatrixLoc(), renderer, Vector3(5.75f, 3.0f, 0.0f));
    player2HeartUI[2] = heartUI6;
    addObject(heartUI6);

    auto decreasePlayerHealthCallback = [this](int a, int b)
    {
        decreasePlayerHealth(a, b);
    };

    EventSystem::getInstance().subscribe("decreasePlayerHealth", decreasePlayerHealthCallback);
}

void FightingGameCanvasManager::decreasePlayerHealth(int playerSide, int health)
{
    if (playerSide == 0) 
    {
        // Decrease Player 1's health
        for (int i = 0; i < 3; ++i) 
        {
            if (i < health) 
            {
                player1HeartUI[i]->setIsActive(true);
            }
            else 
            {
                player1HeartUI[i]->setIsActive(false); 
            }
        }
    }
    else if (playerSide == 1) 
    {
        // Decrease Player 2's health
        for (int i = 0; i < 3; ++i) 
        {
            if (i < health) 
            {
                player2HeartUI[i]->setIsActive(true);
            }
            else 
            {
                player2HeartUI[i]->setIsActive(false); 
            }
        }
    }
}

FightingGameCanvasManager::~FightingGameCanvasManager()
{

}