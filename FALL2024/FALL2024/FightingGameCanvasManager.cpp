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

    Square* bgPostGameMesh = new Square(Vector3(0.0f, 0.0f, 0.0f), 0.95f, renderer.GetShader());
    GameObject* bgPostGame = new GameObject(bgPostGameMesh, renderer.GetModelMatrixLoc());
    bgPostGame->getTransform()->setScale(Vector3(15.0f, 10.0f, 0.0f));
    bgPostGame->getTransform()->setPosition(bgPostGame->getTransform()->getPosition() + Vector3(0.0f, 0.05f, 0.0f));
    addObject(bgPostGame);
    bgPostGame->setIsActive(false);
    this->postGameBg = bgPostGame;

    Square* player1winMesh = new Square(Vector3(0.0f, 0.0f, 1.0f), 0.5f, renderer.GetShader());
    player1winMesh->AddTexture("player1win.png", GL_RGBA);
    GameObject* player1win = new GameObject(player1winMesh, renderer.GetModelMatrixLoc());
    bgPostGame->addChild(player1win);
    player1win->setIsActive(false);
    this->player1Win = player1win;

    Square* player2winMesh = new Square(Vector3(0.0f, 0.0f, 1.0f), 0.5f, renderer.GetShader());
    player2winMesh->AddTexture("player2win.png", GL_RGBA);
    GameObject* player2win = new GameObject(player2winMesh, renderer.GetModelMatrixLoc());
    bgPostGame->addChild(player2win);
    player2win->setIsActive(false);
    this->player2Win = player2win;

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

        if (health <= 0) 
        {
            player2Win->setIsActive(true);
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

        if (health <= 0)
        {
            player1Win->setIsActive(true);
        }
    }

    if (health <= 0)
    {
        startCountDownToPostGame = true;
    }
}

void FightingGameCanvasManager::update(float deltaTime)
{
    if (startCountDownToPostGame) 
    {
        currentCountDownToPostGameUI += deltaTime;
        if (currentCountDownToPostGameUI >= countDownToPostGameUI)
        {
            postGameBg->setIsActive(true);
            startCountDownToPostGame = false;
        }
    }
}

FightingGameCanvasManager::~FightingGameCanvasManager()
{

}