#include "Character.h"
#include "FrameController.h"
#include "InputManager.h"


Character::Character(Mesh* mesh, GLint modelMatrixLoc) : ObjectMesh(mesh, modelMatrixLoc)
{
    movementSpeed = 5.0f;
}

void Character::setHurtBox(BoxCollider2D* newHurtBox)
{
    hurtBox = newHurtBox;
}

void Character::SetAnimatedSquare(AnimatedSquare* animated)
{
    animatedSquare = animated;
}

void Character::cleanup()
{
    if (hurtBox != NULL) 
    {
        delete hurtBox;
    }

    ObjectMesh::cleanup();
}

void Character::update(float deltaTime)
{
    ObjectMesh::update(deltaTime);
}

void Character::updateInput(PlayerInput* input) {
    float deltaX = 0.0f, deltaY = 0.0f;

    // Check if the character is attacking
    if (isAttacking)
    {
        if (animatedSquare != NULL)
        {
            animatedSquare->set_animation(AnimationState::cMK); 
        }

        if (AttackAnimationFinished()) 
        {
            isAttacking = false; // Reset attack state
        }

        // While attacking, skip movement updates
        return;
    }
    else
    {
        // Handle crouching medium kick input (cMK)
        if (InputManager::IsKeyPressed(input->GetcMK()))
        {
            Attack();
            // Prevent movement during the attack
            return;
        }

        // Handle left/right movement
        if (InputManager::IsKeyPressed(input->GetMoveRight())) {
            deltaX += movementSpeed * FrameController::getInstance().getDeltaTime();
            if (animatedSquare != NULL)
            {
                if (faceRight)
                {
                    animatedSquare->set_animation(AnimationState::WalkFront);
                }
                else
                {
                    animatedSquare->set_animation(AnimationState::WalkBack);
                }
            }
        }
        if (InputManager::IsKeyPressed(input->GetMoveLeft())) {
            deltaX -= movementSpeed * FrameController::getInstance().getDeltaTime();
            if (animatedSquare != NULL)
            {
                if (faceRight)
                {
                    animatedSquare->set_animation(AnimationState::WalkBack);
                }
                else
                {
                    animatedSquare->set_animation(AnimationState::WalkFront);
                }
            }
        }

        if (deltaX == 0.0f && deltaY == 0.0f)
        {
            if (animatedSquare != NULL)
            {
                animatedSquare->set_animation(AnimationState::Idle);
            }
        }

        // Apply the movement
        UpdateMovement(deltaX, 0.0f);
    }
}

void Character::UpdateMovement(float deltaX, float deltaY) 
{
    getTransform()->setPosition(getTransform()->getPosition() + Vector3(deltaX, deltaY, 0));
}

void Character::MoveRight()
{
    float deltaX = 0.0f;
    deltaX += movementSpeed * FrameController::getInstance().getDeltaTime();
    if (animatedSquare != NULL)
    {
        if (faceRight)
        {
            animatedSquare->set_animation(AnimationState::WalkFront);
        }
        else
        {
            animatedSquare->set_animation(AnimationState::WalkBack);
        }
    }
}

void Character::MoveLeft()
{
    float deltaX = 0.0f;
    deltaX -= movementSpeed * FrameController::getInstance().getDeltaTime();
    if (animatedSquare != NULL)
    {
        if (faceRight)
        {
            animatedSquare->set_animation(AnimationState::WalkBack);
        }
        else
        {
            animatedSquare->set_animation(AnimationState::WalkFront);
        }
    }
}

void Character::Attack() 
{
    isAttacking = true; // Set attacking state
    if (animatedSquare != NULL)
    {
        animatedSquare->set_animation(AnimationState::cMK); // Set cMK animation
    }
}

void Character::SetFaceRight(bool isRight)
{
    faceRight = isRight;
}

bool Character::AttackAnimationFinished()
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