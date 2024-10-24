#pragma once
#include "ObjectMesh.h"
#include "PlayerInput.h"
#include "AnimatedSquare.h"
#include "BoxCollider2D.h"
class Character : public ObjectMesh
{
public:
    Character(Mesh* mesh, GLint modelMatrixLoc);
    void SetAnimatedSquare(AnimatedSquare* animated);
    void SetFaceRight(bool isRight);

    void updateInput(PlayerInput* input);
    void update(float deltaTime) override;
    void cleanup() override;

    // Character actions (movement, etc.)
    void Move(float deltaX, float deltaY);
    void Jump();
    void Attack();
    bool AttackAnimationFinished();
    BoxCollider2D* getHurtBox();
    void RenderHitbox();

private:
    
    Vector3 velocity;  // Character's current velocity
    AnimatedSquare* animatedSquare;
    BoxCollider2D* hurtBox;
    float movementSpeed;
    float jumpForce;
    bool isOnGround;
    bool faceRight;
    bool isAttacking;
    bool isAttackAnimFinished;

};

