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

    AnimatedCharacter* ryu = new AnimatedCharacter(Vector3(0.0f, 0.0f, 1.0f), 0.5f, renderer.GetShader());
    ryu->AddTexture("Ryu2.png");
    Node* visualHolder = new GameObject(ryu, renderer.GetModelMatrixLoc());
    
    Vector3 pos = getTransform()->getPosition();
    Vector3 scale = Vector3(Vector3(getTransform()->getScale().x / 1.75f, getTransform()->getScale().y, getTransform()->getScale().z));

    Square* squareMesh = new Square(Vector3(pos.x - scale.x, pos.y - scale.y, 0), Vector3(pos.x - scale.x, pos.y + scale.y, 0),
        Vector3(pos.x + scale.x, pos.y + scale.y, 0), Vector3(pos.x + scale.x, pos.y - scale.y, 0), Vector3(0, 1, 0), 0.5f, renderer.GetShader());

    Square* squareMesh2 = new Square(Vector3(pos.x - scale.x, pos.y - scale.y, 0), Vector3(pos.x - scale.x, pos.y + scale.y, 0),
        Vector3(pos.x + scale.x, pos.y + scale.y, 0), Vector3(pos.x + scale.x, pos.y - scale.y, 0), Vector3(1, 0, 0), 0.5f, renderer.GetShader());

    Square* squareMesh3 = new Square(Vector3(pos.x - scale.x, pos.y - scale.y, 0), Vector3(pos.x - scale.x, pos.y + scale.y, 0),
        Vector3(pos.x + scale.x, pos.y + scale.y, 0), Vector3(pos.x + scale.x, pos.y - scale.y, 0), Vector3(0, 1, 0), 0.5f, renderer.GetShader());

    hitBox = new BoxCollider2D(squareMesh2, renderer.GetModelMatrixLoc(), pos, scale);
    hurtBox = new BoxCollider2D(squareMesh, renderer.GetModelMatrixLoc(), pos, scale);
    legHurtBox = new BoxCollider2D(squareMesh3, renderer.GetModelMatrixLoc(), pos, scale);
    //hitBox->setIsDrawingActive(true);
   // hurtBox->setIsDrawingActive(true);
    //legHurtBox->setIsDrawingActive(true);

    if (playerSide == 0)
    {
        getTransform()->setPosition(Vector3(-0.75f, -1.75f, 0.0f));
        visualHolder->getTransform()->setScale(Vector3(4.0f, 4.0f, 3.5f));
    }
    else 
    {
        getTransform()->setPosition(Vector3(0.75f, -1.75f, 0.0f));
        visualHolder->getTransform()->setScale(Vector3(-4.0f, 4.0f, 3.5f));
    }

    if (playerSide == 0)
    {
        Vector3 centerPos = pos - Vector3(1.25f, 0.0f, 0.0f);

        hurtBox->getTransform()->setPosition(centerPos);
        hurtBox->getTransform()->setScale(Vector3(1.0f, 2.0f, 1.0f));
        hitBox->getTransform()->setScale(Vector3(1.0f, 0.5f, 1.0f));
        hitBox->getTransform()->setPosition(Vector3(centerPos.x + 1.75f, -2.0f, 0.0f));
        legHurtBox->getTransform()->setScale(Vector3(0.75f, 0.5f, 1.0f));
        legHurtBox->getTransform()->setPosition(Vector3(centerPos.x + 0.75f, -2.0f, 0.0f));
    }
    else
    {
        Vector3 centerPos = pos + Vector3(1.25f, 0.0f, 0.0f);

        hurtBox->getTransform()->setPosition(centerPos);
        hurtBox->getTransform()->setScale(Vector3(1.0f, 2.0f, 1.0f));
        hitBox->getTransform()->setScale(Vector3(1.0f, 0.5f, 1.0f));
        hitBox->getTransform()->setPosition(Vector3(centerPos.x - 1.75f, -2.0f, 0.0f));
        legHurtBox->getTransform()->setScale(Vector3(0.75f, 0.5f, 1.0f));
        legHurtBox->getTransform()->setPosition(Vector3(centerPos.x - 0.75f, -2.0f, 0.0f));
    }

    setAnimatedSquare(ryu);

    hitBox->setIsActive(false);
    legHurtBox->setIsActive(false);

    addChild(visualHolder);
    addChild(hurtBox);
    addChild(hitBox);
    addChild(legHurtBox);

    addPhysicsComponent(1.0f);
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
    hitBox->setIsActive(false);
    animatedCharacter->setAnimation(AnimationState::Idle);
}

void Character::setHurtBox(BoxCollider2D* newHurtBox)
{
    hurtBox = newHurtBox;
}

void Character::setAnimatedSquare(AnimatedCharacter* animated)
{
    animatedCharacter = animated;
}

void Character::cleanup()
{
    if (hitBox != NULL) 
    {
        delete hitBox;
    }

    if (hurtBox != NULL) 
    {
        delete hurtBox;
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
    float sign = 1.0f;

    if (playerSide == 0) 
    {
        sign = -1.0f;
    }
    else 
    {
        sign = 1.0f;
    }

    Vector3 centerPos = legHurtBox->getTransform()->getPosition();//+ Vector3(sign * 0.75f, -2.0f, 0.0f);

    if (animatedCharacter != NULL) 
    {
        if (legHurtBox != NULL)
        {
            if (animatedCharacter->isAtFrame(2) || animatedCharacter->isAtFrame(5))
            {
                legHurtBox->getTransform()->setScale(Vector3(0.75f, 0.5f, 1.0f));
                legHurtBox->getTransform()->setPosition(Vector3((sign * 0.25f), centerPos.y, 0));
            }
            else if (animatedCharacter->isAtFrame(3) || animatedCharacter->isAtFrame(4))
            {
                legHurtBox->getTransform()->setScale(Vector3(1.8f, 0.5f, 1.0f));
                legHurtBox->getTransform()->setPosition(Vector3((sign * -0.1f), centerPos.y, 0));
            }
            else
            {
                legHurtBox->getTransform()->setScale(Vector3(0.25f, 0.5f, 1.0f));
                legHurtBox->getTransform()->setPosition(Vector3((sign * 2.0f), centerPos.y, 0));
            }
        }
    }
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

    legHurtBox->setIsActive(isAttacking);
    // Check if the character is attacking
    if (isAttacking)
    {
        if (animatedCharacter != NULL)
        {
            animatedCharacter->setAnimation(AnimationState::cMK);

            hitBox->setIsActive(animatedCharacter->isAtFrame(3));

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
            hitBox->setIsActive(false); // Disable hitbox while blocking

            isBlocking = false; // End block state when animation finishes

            return;
        }
    }
}

void Character::executeThrow()
{
    isThrowing = true; // Set to attacking state
    //youWin = true;
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
        hitBox->setIsActive(false); // Deactivate hitbox in blocking mode
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
    hitBox->setIsActive(false); // Disable hitbox while in hurt state
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

    //printf("player side %f: updatemovement %f %f  \n", playerSide, deltaX, deltaY);

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

BoxCollider2D* Character::getHurtBox()
{
    return hurtBox;
}

BoxCollider2D* Character::getHitBox()
{
    return hitBox;
}

BoxCollider2D* Character::getLegHurtBox()
{
    return legHurtBox;
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
        /*printf("playerside: %f\n", playerSide);
        printf("MY POS: %f %f %f \n", getTransform()->getPosition().x, getTransform()->getPosition().y, getTransform()->getPosition().z);
        printf("Oppo POS: %f %f %f \n", oppoVector.x, oppoVector.y, oppoVector.z);
        printf("diff POS: %f %f %f \n", newVector.x, newVector.y, newVector.z);
        printf("distance: %f\n\n", distance);*/
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