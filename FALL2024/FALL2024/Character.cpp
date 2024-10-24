#include "Character.h"
#include "FrameController.h"
#include "InputManager.h"


Character::Character(Mesh* mesh, GLint modelMatrixLoc) : ObjectMesh(mesh, modelMatrixLoc)
{
    velocity = Vector3(0.0f, 0.0f, 0.0f);
    movementSpeed = 5.0f;
    jumpForce = 10.0f;
    isOnGround = true;
    Vector3 pos = getTransform()->getPosition();
    Vector3 scale = getTransform()->getScale();

    hurtBox = new BoxCollider2D(pos.x, pos.y, scale.x, scale.y);


}

void Character::RenderHitbox()
{
    
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

    //position = position + velocity;

    // Apply some basic gravity simulation for jumping
    /*if (!isOnGround)
    {
        velocity.y -= 0.5f;  // Gravity
        if (position.y <= 0.0f) {
            position.y = 0.0f;
            isOnGround = true;
            velocity.y = 0.0f;
        }
    }*/

    ObjectMesh::update(deltaTime);
}

void Character::updateInput(PlayerInput* input) {
    float deltaX = 0.0f, deltaY = 0.0f;

    // Check if the character is attacking
    if (isAttacking)
    {
        if (animatedSquare != NULL)
        {
            animatedSquare->set_animation(AnimationState::cMK); // Set cMK animation
        }

        // Optionally, handle timing to reset the attack state
        if (AttackAnimationFinished()) // You need a way to check this
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
            isAttacking = true; // Set attacking state
            if (animatedSquare != NULL)
            {
                animatedSquare->set_animation(AnimationState::cMK); // Set cMK animation
            }

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
        Move(deltaX, 0.0f);
    }



    // Example for gamepad input
    /*float leftX, leftY;
    input.GetGamepadAxes(leftX, leftY);*/

    // Apply movement from gamepad's left stick
    //Move(leftX * movementSpeed, 0.0f);

    // Update the position with velocity (e.g., gravity)
}

void Character::Move(float deltaX, float deltaY) {
    getTransform()->setPosition(getTransform()->getPosition() + Vector3(deltaX, deltaY, 0));
}

void Character::Jump() {
    if (isOnGround) {
        velocity.y = jumpForce;
        isOnGround = false;
        std::cout << "Character jumped!" << std::endl;
    }
}

void Character::Attack() {
    std::cout << "Character attacked!" << std::endl;
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