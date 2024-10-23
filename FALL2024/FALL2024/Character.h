#pragma once
#include "ObjectMesh.h"
#include "PlayerInput.h"
class Character : public ObjectMesh
{
public:
    Character(Mesh* mesh, GLint modelMatrixLoc);

    void updateInput(PlayerInput* input);
    void update(float deltaTime) override;

    // Character actions (movement, etc.)
    void Move(float deltaX, float deltaY);
    void Jump();
    void Attack();

private:
    Vector3 velocity;  // Character's current velocity

    float movementSpeed;
    float jumpForce;
    bool isOnGround;
};

