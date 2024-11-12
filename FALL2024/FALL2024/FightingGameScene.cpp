#include "FightingGameScene.h"
#include "FightingGameManager.h"
#include "FightingGameCanvasManager.h"

FightingGameScene::FightingGameScene(Camera* cam, Renderer& rend, GameWindow& wind)
	: Scene(cam, rend, wind)
{
	leftBoundary = -5.5f;
	rightBoundary = 5.5f;
}

void FightingGameScene::assignObjects()
{
    Square* bgMesh = new Square(Vector3(0.0f, 0.0f, 1.0f), 0.5f, renderer.GetShader());
    bgMesh->AddTexture("bg2.png", GL_RGB);
    GameObject* bg = new GameObject(bgMesh, renderer.GetModelMatrixLoc());
    bg->getTransform()->setScale(Vector3(15.0f, 10.0f, 0.0f));
    addObject(bg);

    player1Controller = new PlayerInput(0, KeyboardMouse, window);
    player2Controller = new PlayerInput(1, KeyboardMouse, window);

    character1 = new Character(NULL, renderer.GetModelMatrixLoc(), renderer, 0);
    character1->setFaceRight(true);
    addObject(character1);

    character2 = new Character(NULL, renderer.GetModelMatrixLoc(), renderer, 1);
    addObject(character2);
    
    character1->setOpponent(character2);
    character2->setOpponent(character1);

    canvas = new FightingGameCanvasManager(renderer);

    FightingGameManager::getInstance().initialize(character1, character2);

    Scene::assignObjects();
}

void FightingGameScene::update(float deltaTime) 
{
    if (player1Controller)
    {
        player1Controller->Update();
        character1->updateInput(player1Controller);

    }
    if (player2Controller)
    {
        player2Controller->Update();
        character2->updateInput(player2Controller);
    }

    handleCollision();

    character1->setCanHitConfirm(character2->getIsHurt());
    character2->setCanHitConfirm(character1->getIsHurt());
    character1->setYouLose(character2->getHitConfirmSuccess() || character1->getIsBeingThrown());
    character2->setYouLose(character1->getHitConfirmSuccess() || character2->getIsBeingThrown());

    Scene::update(deltaTime);

    FightingGameManager::getInstance().update(deltaTime);
}

void FightingGameScene::handleCollision() 
{
    /*Player1 Player2 Collision*/

    /*if (character1->getHurtBox()->isColliding(*character2->getHurtBox()))
    {
        float pushbackDistance = 0.1f; // Adjust this value to control the pushback strength 

        // Get current positions
        Vector3 position1 = character1->getTransform()->getPosition();
        Vector3 position2 = character2->getTransform()->getPosition();

        // Determine direction of pushback
        if (position1.x < position2.x)
        {
            // character1 is to the left, so push it left and character2 right
            character1->getTransform()->setPosition(Vector3(position1.x + pushbackDistance, position1.y, position1.z));
            character2->getTransform()->setPosition(Vector3(position2.x - pushbackDistance, position2.y, position2.z));
        }
        else
        {
            // character1 is to the right, so push it right and character2 left
            character1->getTransform()->setPosition(Vector3(position1.x - pushbackDistance, position1.y, position1.z));
            character2->getTransform()->setPosition(Vector3(position2.x + pushbackDistance, position2.y, position2.z));
        }
    }*/

    /*If Attack Happens*/
    //character1->isOpponentWithinThrowRange();
    //character2->isOpponentWithinThrowRange();
    //printf("character 2 in range: %i\n", character1->isWithinThrowRange());
    //printf("character 1 in range: %i\n", character2->isWithinThrowRange());

    /*if (character1->getHitBox()->isColliding(*character2->getHurtBox())
        || character1->getHitBox()->isColliding(*character2->getLegHurtBox()))
    {
        character2->triggerHurt();
    }

    if (character2->getHitBox()->isColliding(*character1->getHurtBox())
        || character2->getHitBox()->isColliding(*character1->getLegHurtBox()))
    {
        character1->triggerHurt();
    }*/

    /*Player Wall Collision*/

    // Check if characters are within the defined boundaries
    Vector3 position1 = character1->getTransform()->getPosition();
    Vector3 position2 = character2->getTransform()->getPosition();

    // Clamp character1's position within the boundaries
    if (position1.x < leftBoundary)
    {
        character1->getTransform()->setPosition(Vector3(leftBoundary, position1.y, position1.z));
    }
    else if (position1.x > rightBoundary + 1.75f)
    {
        character1->getTransform()->setPosition(Vector3(rightBoundary + 1.75f, position1.y, position1.z));
    }

    // Clamp character2's position within the boundaries
    if (position2.x < leftBoundary - 1.75f)
    {
        character2->getTransform()->setPosition(Vector3(leftBoundary - 1.75f, position2.y, position2.z));
    }
    else if (position2.x > rightBoundary)
    {
        character2->getTransform()->setPosition(Vector3(rightBoundary, position2.y, position2.z));
    }
}

FightingGameScene::~FightingGameScene()
{
    if (player1Controller != NULL)
    {
        delete player1Controller;
    }

    if (player2Controller != NULL)
    {
        delete player2Controller;
    }
}