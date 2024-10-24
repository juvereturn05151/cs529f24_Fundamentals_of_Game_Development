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

    void MoveRight();
    void MoveLeft();
    void Attack();
    bool AttackAnimationFinished();
    void setHurtBox(BoxCollider2D* newHurtBox);
    BoxCollider2D* getHurtBox();

private:
    float deltaX = 0.0f, deltaY = 0.0f;
    AnimatedSquare* animatedSquare;
    BoxCollider2D* hurtBox;
    float movementSpeed;
    bool faceRight;
    bool isAttacking;
    bool isAttackAnimFinished;

    void UpdateMovement(PlayerInput* input);

};

