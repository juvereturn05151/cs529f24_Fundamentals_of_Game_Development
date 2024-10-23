#pragma once
#include "ObjectMesh.h"
#include "PlayerInput.h"
#include "AnimatedSquare.h"
class Character : public ObjectMesh
{
public:
    Character(Mesh* mesh, GLint modelMatrixLoc);
    void SetAnimatedSquare(AnimatedSquare* animated);
    void SetFaceRight(bool isRight);

    void updateInput(PlayerInput* input);
    void update(float deltaTime) override;

    // Character actions (movement, etc.)
    void Move(float deltaX, float deltaY);
    void Jump();
    void Attack();
    void SetAttackAnimFinished(bool attack);
    bool AttackAnimationFinished();

private:
    
    Vector3 velocity;  // Character's current velocity
    AnimatedSquare* animatedSquare;
    float movementSpeed;
    float jumpForce;
    bool isOnGround;
    bool faceRight;
    bool isAttacking;
    bool isAttackAnimFinished;

};

