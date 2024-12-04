#include "Character.h"
#include "FrameController.h"
#include "InputManager.h"
#include "EventSystem.h"
#include <algorithm>
#include "SoundManager.h"

Character::Character(Mesh* mesh, GLint modelMatrixLoc, Renderer& renderer, int playerSide) : GameObject(mesh, modelMatrixLoc)
{
    this->playerSide = playerSide;
    movementSpeed = 5.0f;
    health = 3;

    setupVisuals(renderer);
    characterCollisionManager = new CharacterCollisionManager(renderer, getTransform()->getPosition(), 
        Vector3(Vector3(getTransform()->getScale().x / 1.75f, getTransform()->getScale().y, getTransform()->getScale().z)));

    if (playerSide == 0)
    {
        getTransform()->setPosition(Vector3(-0.75f, -1.75f, 0.0f));
    }
    else 
    {
        getTransform()->setPosition(Vector3(0.75f, -1.75f, 0.0f));
    }

    characterCollisionManager->setupHitboxes(getTransform()->getPosition(), playerSide);
    
    addChild(characterCollisionManager->getHurtBox());
    addChild(characterCollisionManager->getHitBox());
    addChild(characterCollisionManager->getLegHurtBox());

    addPhysicsComponent(1.0f);
}

// Helper for Visual Setup
void Character::setupVisuals(Renderer& renderer)
{
    animatedCharacter = new AnimatedCharacter(Vector3(-1.5f, -0.5f, 0.0f), Vector3(-1.5f, 0.5f, 0.0f), Vector3(1.5f, 0.5f, 0.0f), Vector3(1.5f, -0.5f, 0.0f)
        , 1.0f/15.0f,1.0f/11.0f,Vector3(0.0f, 0.0f, 1.0f), 0.5f, renderer.GetShader());
    animatedCharacter->AddTexture("sheet_05.png");
    GameObject * visualHolder = new GameObject(animatedCharacter, renderer.GetModelMatrixLoc());

    if (playerSide == 0)
    {
        visualHolder->getTransform()->setScale(Vector3(3.0f, 4.0f, 3.5f));
        visualHolder->getTransform()->translate(Vector3(-0.5f, -0.1f, 0.0f));
    }
    else
    {
        visualHolder->getTransform()->setScale(Vector3(-3.0f, 4.0f, 3.5f));
        visualHolder->getTransform()->translate(Vector3(-0.5f, -0.1f, 0.0f));
    }

    addChild(visualHolder);
}

void Character::reset()
{
    isAttacking = false;
    isAttackAnimFinished = false;
    isHurt = false;
    canHitConfirm = false;
    hitConfirmSuccess = false;
    youWin = false;
    youLose = false;
    isBlocking = false;
    block = false;
    hasPlayUrghSound = false;
    hasPlayHitConfirmSound = false;
    isReadyToFight = false;
    beingThrown = false;
    isThrowing = false;
    characterCollisionManager->getHitBox()->setIsActive(false);
    animatedCharacter->setAnimation(AnimationState::Idle);
    physicsComp->setVelocity(Vector3(0, 0, 0));
}

void Character::cleanup()
{
    if (characterCollisionManager != NULL) 
    {
        delete characterCollisionManager;
    }

    GameObject::cleanup();
}

void Character::update(float deltaTime)
{
    if (animatedCharacter != NULL)
    {
        animatedCharacter->updateAnimation(deltaTime);
    }

    GameObject::update(deltaTime);
}

void Character::draw()
{
    GameObject::draw();
}


void Character::updateCMKCollider()
{
    characterCollisionManager->updateLegHitBox(animatedCharacter, playerSide);
}

bool Character::getHitConfirmSuccess()
{
    return hitConfirmSuccess;
}

void Character::updateInput(PlayerInput* input) 
{
    if (!isReadyToFight) 
    {
        return;
    }

    block = false;

    if (youLose)
    {
        if (animatedCharacter->getCurrentState() != AnimationState::YouLose) 
        {
            animatedCharacter->setAnimation(AnimationState::YouLose, false);
            health--;
            health = std::clamp(health, 0, 3);
            EventSystem::getInstance().notify("decreasePlayerHealth", playerSide, health);
        }

        if (animatedCharacter->getCurrentState() == AnimationState::YouLose)
        {
            if (animatedCharacter->isAtFrame(5))
            {
                getPhysicsComp()->setIsActive(true);

                if (!hasPlayUrghSound)
                {
                    SoundManager::getInstance().playSound("audio/ryuken-uggh-101soundboards.mp3", false);
                    hasPlayUrghSound = true;
                }

                if (playerSide == 0)
                {
                    physicsComp->applyForce(Vector3(-250.0f, 0.0f, 0.0f));
                }
                else
                {
                    physicsComp->applyForce(Vector3(250.0f, 0.0f, 0.0f));
                }
            }
        }

        return;
    }


    if (beingThrown)
    {
        return;
    }

    if (hitConfirmSuccess) 
    {
        if (animatedCharacter->isAtFrame(3)) 
        {
            if (!hasPlayHitConfirmSound) 
            {
                if (animatedCharacter->getCurrentState() != AnimationState::YouWin)
                {
                    hasPlayHitConfirmSound = true;
                    SoundManager::getInstance().playSound("audio/hitconfirm.wav", false);
                }
            }
        }

        if (isAnimationFinished() && !youWin) 
        {
            youWin = true;
            SoundManager::getInstance().playSound("audio/you-win-street-fighter-101soundboards.mp3", false);
            animatedCharacter->setAnimation(AnimationState::YouWin, false);
        }

        return;
    }

    if (canHitConfirm) 
    {
        if (!hitConfirmSuccess) 
        {
            if (InputManager::IsKeyJustPressed(input->GetcMK()) || InputManager::IsGamepadButtonJustPressed(input->GetcMKController(), playerSide))
            {
                SoundManager::getInstance().playSound("audio/ryuken-hadooken-101soundboards.mp3", false);
                hitConfirmSuccess = true;
                if (animatedCharacter->getCurrentState() != AnimationState::Hadoken)
                {
                    SoundManager::getInstance().playSound("audio/hitconfirm.wav", false);
                }
                animatedCharacter->setAnimation(AnimationState::Hadoken);
                return;
            }
        }
    }

    if (isHurt) 
    {
        if (animatedCharacter != NULL) 
        {
            animatedCharacter->setAnimation(AnimationState::Hurt);
        }

        // Skip other updates while hurt
        if (isAnimationFinished()) 
        {
            isHurt = false; // End hurt state once animation is done
        }

        return;
    }

    if (isThrowing) 
    {
        if (animatedCharacter != NULL)
        {
            if (!youWin) 
            {
                if (animatedCharacter->getCurrentState() != AnimationState::Throw)
                {
                    animatedCharacter->setAnimation(AnimationState::Throw, false);
                }

                if (animatedCharacter->getCurrentState() == AnimationState::Throw)
                {
                    if (animatedCharacter->isAtFrame(5))
                    {
                        youWin = true;
                        SoundManager::getInstance().playSound("audio/you-win-street-fighter-101soundboards.mp3", false);
                    }
                }
            }
        }

        return;
    }

    characterCollisionManager->getLegHurtBox()->setIsActive(isAttacking);
    // Check if the character is attacking
    if (isAttacking)
    {
        if (animatedCharacter != NULL)
        {
            animatedCharacter->setAnimation(AnimationState::cMK);
            characterCollisionManager->getHitBox()->setIsActive(animatedCharacter->isAtFrame(3));
            updateCMKCollider();
        }

        if (isAnimationFinished()) 
        {
            isAttacking = false; // Reset attack state
        }

        // While attacking, skip movement updates
        return;
    }
    else
    {
        if (isOpponentWithinThrowRange())
        {
            if (InputManager::IsKeyJustPressed(input->GetcMK()) || InputManager::IsGamepadButtonPressed(input->GetcMKController(), playerSide))
            {
                if (playerSide == 0 && (InputManager::IsKeyPressed(input->GetMoveRight()) || InputManager::IsGamepadButtonPressed(input->GetMoveRightController(), playerSide)))
                {
                    executeThrow(); 
                    return;
                }
                else if (playerSide == 1 && (InputManager::IsKeyPressed(input->GetMoveLeft()) || InputManager::IsGamepadButtonPressed(input->GetMoveLeftController(), playerSide)))
                {
                    executeThrow();
                    return;
                }
            }
        }

        // Handle crouching medium kick input (cMK)
        if (InputManager::IsKeyJustReleased(input->GetcMK()) || InputManager::IsGamepadButtonJustPressed(input->GetcMKController(), playerSide))
        {  
            attack();
            // Prevent movement during the attack
            return;
        }

        // Apply the movement
        updateMovement(input);

        if (isBlocking)
        {
            animatedCharacter->setAnimation(AnimationState::Block); // Set blocking animation
            characterCollisionManager->getHitBox()->setIsActive(false); // Disable hitbox while blocking
            isBlocking = false; // End block state when animation finishes
            return;
        }
    }
}

void Character::executeThrow()
{
    isThrowing = true; // Set to attacking state
    float xOffset = 0;
    if (playerSide == 0) 
    {
        xOffset = -1.75f;
    }
    else
    {
        xOffset = 1.75f;
    }
    opponent->getPhysicsComp()->setIsActive(false);
    opponent->getTransform()->setPosition(getTransform()->getPosition() + Vector3(xOffset,2.0f,0.0f));
    opponent->setBeingThrown(true);
}

void Character::checkForBlock(PlayerInput* input)
{
    bool facingOpponent = (playerSide == 0 && !(InputManager::IsKeyPressed(input->GetMoveRight()) || InputManager::IsGamepadButtonPressed(input->GetMoveRightController(), playerSide))) ||
        (playerSide == 1 && !( InputManager::IsKeyPressed(input->GetMoveLeft()) || InputManager::IsGamepadButtonPressed(input->GetMoveLeftController(), playerSide)));

    if (facingOpponent)
    {
        isBlocking = true;
        animatedCharacter->setAnimation(AnimationState::Block); // Set to blocking animation
        characterCollisionManager->getHitBox()->setIsActive(false);
        //hitBox->setIsActive(false); // Deactivate hitbox in blocking mode
    }
}

void Character::triggerHurt() 
{
    if (block) 
    {
        if (!isBlocking)
        {
            isBlocking = true;
            if (animatedCharacter->getCurrentState() != AnimationState::Block) 
            {
                SoundManager::getInstance().playSound("audio/guard-101soundboards.mp3", false);
            }
        }
        
        return;
    }

    if (youLose) 
    {
        return;
    }

    isHurt = true;  // Set hurt state

    if (animatedCharacter != NULL) 
    {
        if (animatedCharacter->getCurrentState() != AnimationState::Hurt) 
        {
            animatedCharacter->setAnimation(AnimationState::Hurt);
            SoundManager::getInstance().playSound("audio/hit.wav", false);
        }
    }

    characterCollisionManager->getHitBox()->setIsActive(false);
   // hitBox->setIsActive(false); // Disable hitbox while in hurt state
}


void Character::updateMovement(PlayerInput* input)
{
    deltaX = 0.0f, deltaY = 0.0f;
    // Handle left/right movement
    if (InputManager::IsKeyPressed(input->GetMoveRight()) || InputManager::IsGamepadButtonPressed(input->GetMoveRightController(), playerSide))
    {
        moveRight();

        if (playerSide == 1)
        {
            block = true;
        }
    }
    if ( InputManager::IsKeyPressed(input->GetMoveLeft()) || InputManager::IsGamepadButtonPressed(input->GetMoveLeftController(), playerSide))
    {
        moveLeft();

        if (playerSide == 0) 
        {
            block = true;
        }
    }

    if (deltaX == 0.0f && deltaY == 0.0f)
    {
        if (animatedCharacter != NULL)
        {
            animatedCharacter->setAnimation(AnimationState::Idle);
        }
    }

    getTransform()->setPosition(getTransform()->getPosition() + Vector3(deltaX, deltaY, 0));
}

void Character::moveRight()
{
    deltaX += movementSpeed * FrameController::getInstance().getDeltaTime();
    if (animatedCharacter != NULL)
    {
        if (faceRight)
        {
            animatedCharacter->setAnimation(AnimationState::WalkFront);
        }
        else
        {
            animatedCharacter->setAnimation(AnimationState::WalkBack);
        }
    }
}

void Character::moveLeft()
{
    deltaX -= movementSpeed * FrameController::getInstance().getDeltaTime();
    if (animatedCharacter != NULL)
    {
        if (faceRight)
        {
            animatedCharacter->setAnimation(AnimationState::WalkBack);
        }
        else
        {
            animatedCharacter->setAnimation(AnimationState::WalkFront);
        }
    }
}

void Character::attack() 
{
    isAttacking = true; // Set attacking state
    SoundManager::getInstance().playSound("audio/ryu_attack_sound.mp3", false);
    if (animatedCharacter != NULL)
    {
        animatedCharacter->setAnimation(AnimationState::cMK); // Set cMK animation
    }
}

void Character::setFaceRight(bool isRight)
{
    faceRight = isRight;
}

bool Character::isAnimationFinished()
{
    if (animatedCharacter != NULL) 
    {
        return animatedCharacter->isAnimationFinished();
    }

    return false;
}

void Character::setCanHitConfirm(bool isEnemyHurt)
{
    canHitConfirm = isEnemyHurt;
}

bool Character::getCanHitConfirm()
{
    return canHitConfirm;
}

bool Character::getIsHurt()
{
    return isHurt;
}

void Character::setYouWin(bool win)
{
    youWin = win;
}

bool  Character::getYouWin()
{
    return youWin;
}

void Character::setYouLose(bool lose)
{
    youLose = lose;
}

int Character::getHealth()
{
    return health;
}

void Character::setIsReadyToFight(bool isReady)
{
    isReadyToFight = isReady;
}

void Character::setOpponent(Character* opponent)
{
    this->opponent = opponent;
}

bool Character::isOpponentWithinThrowRange()
{
    if (opponent != NULL) 
    {
        Vector3 oppoVector;

        if (playerSide == 0)
        {
            oppoVector = opponent->getTransform()->getPosition() + Vector3(1.75f,0.0f,0.0f);
        }
        else 
        {
            oppoVector = opponent->getTransform()->getPosition() - Vector3(1.75f, 0.0f, 0.0f);
        }

        Vector3 newVector = getTransform()->getPosition() - oppoVector;
        float distance = (newVector).magnitude();
        return distance < 0.6f; // Adjust the distance threshold as needed
    }

    return false;
}

bool Character::getIsThrowing()
{
    return isThrowing;
}

bool Character::getIsBeingThrown()
{
    return beingThrown;
}

void Character::setBeingThrown(bool thrown)
{
    beingThrown = true;
}

CharacterCollisionManager* Character::getCharacterCollisionManager()
{
    return characterCollisionManager;
}