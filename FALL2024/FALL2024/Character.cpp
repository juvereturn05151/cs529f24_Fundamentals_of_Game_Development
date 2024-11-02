#include "Character.h"
#include "FrameController.h"
#include "InputManager.h"

Character::Character(Mesh* mesh, GLint modelMatrixLoc) : GameObject(mesh, modelMatrixLoc)
{
    movementSpeed = 5.0f;
}

Character::Character(Mesh* mesh, GLint modelMatrixLoc, Renderer& renderer, int playerSide) : GameObject(mesh, modelMatrixLoc)
{
    this->playerSide = playerSide;
    movementSpeed = 5.0f;

    AnimatedSquare* ryu = new AnimatedSquare(Vector3(0.0f, 0.0f, 1.0f), 0.5f, renderer.GetShader());
    ryu->AddTexture();
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

    if (playerSide == 0)
    {
        getTransform()->setPosition(Vector3(-0.75f, 0.0f, 0.0f));
        visualHolder->getTransform()->setScale(Vector3(3.5f, 3.5f, 3.5f));
    }
    else 
    {
        getTransform()->setPosition(Vector3(0.75f, 0.0f, 0.0f));
        visualHolder->getTransform()->setScale(Vector3(-3.5f, 3.5f, 3.5f));
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

void Character::setHurtBox(BoxCollider2D* newHurtBox)
{
    hurtBox = newHurtBox;
}

void Character::setAnimatedSquare(AnimatedSquare* animated)
{
    animatedSquare = animated;
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
    if (animatedSquare != NULL)
    {
        animatedSquare->updateAnimation(deltaTime);
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

    if (animatedSquare != NULL) 
    {
        if (legHurtBox != NULL)
        {
            if (animatedSquare->isAtFrame(2) || animatedSquare->isAtFrame(5))
            {
                legHurtBox->getTransform()->setScale(Vector3(0.75f, 0.5f, 1.0f));
                legHurtBox->getTransform()->setPosition(Vector3((sign * 0.25f), centerPos.y, 0));
            }
            else if (animatedSquare->isAtFrame(3) || animatedSquare->isAtFrame(4))
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
    block = false;

    if (youLose)
    {
        if (animatedSquare->getCurrentState() != AnimationState::YouLose) 
        {
            animatedSquare->setAnimation(AnimationState::YouLose, false);
        }

        if (animatedSquare->isAtFrame(5)) 
        {
            if (playerSide == 0)
            {
                physicsComp->applyForce(Vector3(-250.0f, 0.0f, 0.0f));
            }
            else
            {
                physicsComp->applyForce(Vector3(250.0f, 0.0f, 0.0f));
            }
        }

        return;
    }

    if (hitConfirmSuccess) 
    {
        if (isAnimationFinished() && !youWin) 
        {
            youWin = true;
            animatedSquare->setAnimation(AnimationState::YouWin, false);
        }

        return;
    }

    if (canHitConfirm) 
    {
        if (!hitConfirmSuccess) 
        {
            if (InputManager::IsKeyJustPressed(input->GetcMK()))
            {
                hitConfirmSuccess = true;
                animatedSquare->setAnimation(AnimationState::Hadoken);
                return;
            }
        }
    }

    if (isHurt) 
    {
        if (animatedSquare != NULL) 
        {
            animatedSquare->setAnimation(AnimationState::Hurt);
        }

        // Skip other updates while hurt
        if (isAnimationFinished()) 
        {
            isHurt = false; // End hurt state once animation is done
        }

        return;
    }

    legHurtBox->setIsActive(isAttacking);
    // Check if the character is attacking
    if (isAttacking)
    {
        if (animatedSquare != NULL)
        {
            animatedSquare->setAnimation(AnimationState::cMK);

            hitBox->setIsActive(animatedSquare->isAtFrame(3));

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


        // Handle crouching medium kick input (cMK)
        if (InputManager::IsKeyJustPressed(input->GetcMK()))
        {
            
            attack();
            // Prevent movement during the attack
            return;
        }

        // Apply the movement
        updateMovement(input);

        if (isBlocking)
        {
            animatedSquare->setAnimation(AnimationState::Block); // Set blocking animation
            hitBox->setIsActive(false); // Disable hitbox while blocking

            if (isAnimationFinished())
            {
                isBlocking = false; // End block state when animation finishes
            }

            return;
        }
    }
}

void Character::checkForBlock(PlayerInput* input)
{
    bool facingOpponent = (playerSide == 0 && !InputManager::IsKeyPressed(input->GetMoveRight())) ||
        (playerSide == 1 && !InputManager::IsKeyPressed(input->GetMoveLeft()));

    if (facingOpponent)
    {
        isBlocking = true;
        animatedSquare->setAnimation(AnimationState::Block); // Set to blocking animation
        hitBox->setIsActive(false); // Deactivate hitbox in blocking mode
    }
}

void Character::triggerHurt() 
{
    if (block) 
    {
        isBlocking = true;
        return;
    }

    if (youLose) 
    {
        return;
    }

    isHurt = true;  // Set hurt state

    if (animatedSquare != NULL) 
    {
        animatedSquare->setAnimation(AnimationState::Hurt);
    }
    hitBox->setIsActive(false); // Disable hitbox while in hurt state
}


void Character::updateMovement(PlayerInput* input)
{
    deltaX = 0.0f, deltaY = 0.0f;
    // Handle left/right movement
    if (InputManager::IsKeyPressed(input->GetMoveRight())) 
    {
        moveRight();

        if (playerSide == 1)
        {
            block = true;
        }
    }
    if (InputManager::IsKeyPressed(input->GetMoveLeft())) 
    {
        moveLeft();

        if (playerSide == 0) 
        {
            block = true;
        }
    }

    if (deltaX == 0.0f && deltaY == 0.0f)
    {
        if (animatedSquare != NULL)
        {
            animatedSquare->setAnimation(AnimationState::Idle);
        }
    }

    getTransform()->setPosition(getTransform()->getPosition() + Vector3(deltaX, deltaY, 0));
}

void Character::moveRight()
{
    deltaX += movementSpeed * FrameController::getInstance().getDeltaTime();
    if (animatedSquare != NULL)
    {
        if (faceRight)
        {
            animatedSquare->setAnimation(AnimationState::WalkFront);
        }
        else
        {
            animatedSquare->setAnimation(AnimationState::WalkBack);
        }
    }
}

void Character::moveLeft()
{
    deltaX -= movementSpeed * FrameController::getInstance().getDeltaTime();
    if (animatedSquare != NULL)
    {
        if (faceRight)
        {
            animatedSquare->setAnimation(AnimationState::WalkBack);
        }
        else
        {
            animatedSquare->setAnimation(AnimationState::WalkFront);
        }
    }
}

void Character::attack() 
{
    isAttacking = true; // Set attacking state
    if (animatedSquare != NULL)
    {
        animatedSquare->setAnimation(AnimationState::cMK); // Set cMK animation
    }
}

void Character::setFaceRight(bool isRight)
{
    faceRight = isRight;
}

bool Character::isAnimationFinished()
{
    if (animatedSquare != NULL) 
    {
        return animatedSquare->isAnimationFinished();
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