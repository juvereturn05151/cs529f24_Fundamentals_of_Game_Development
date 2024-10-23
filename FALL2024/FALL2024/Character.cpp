#include "Character.h"
#include "FrameController.h"


Character::Character(Mesh* mesh, GLint modelMatrixLoc) : ObjectMesh(mesh, modelMatrixLoc)
{
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	movementSpeed = 5.0f;
	jumpForce = 10.0f;
	isOnGround = true;
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

    // Handle left/right movement
    if (input->IsKeyPressed(input->GetMoveRight())) {
        deltaX += movementSpeed * FrameController::getInstance().getDeltaTime();
    }
    if (input->IsKeyPressed(input->GetMoveLeft())) {
        deltaX -= movementSpeed * FrameController::getInstance().getDeltaTime();
    }

    // Handle jumping (only if the character is on the ground)
    /*if (input.IsKeyPressed(GLFW_KEY_SPACE) && isOnGround) {
        Jump();
    }*/

    // Apply the movement
    Move(deltaX, 0.0f);

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