#pragma once
#include "ObjectMesh.h"
#include "PlayerInput.h"
#include "AnimatedSquare.h"
#include "BoxCollider2D.h"
#include "Renderer.h"
class Character : public ObjectMesh
{
public:
    Character(Mesh* mesh, GLint modelMatrixLoc);
    Character(Mesh* mesh, GLint modelMatrixLoc, Renderer& renderer, int playerSide = 1);
    void SetAnimatedSquare(AnimatedSquare* animated);
    void SetFaceRight(bool isRight);

    void updateInput(PlayerInput* input);
    void update(float deltaTime) override;
    void cleanup() override;
    void draw() override;
    // Character actions (movement, etc.)

    void MoveRight();
    void MoveLeft();
    void Attack();
    void TriggerHurt();
    bool IsAnimationFinished();
    void setHurtBox(BoxCollider2D* newHurtBox);
    BoxCollider2D* getHurtBox();
    BoxCollider2D* getLegHurtBox();
    BoxCollider2D* getHitBox();
    void setCanHitConfirm(bool isEnemyHurt);
    bool getCanHitConfirm();
    bool getIsHurt();

private:
    float deltaX = 0.0f, deltaY = 0.0f;
    float playerSide;
    AnimatedSquare* animatedSquare;
    BoxCollider2D* hurtBox;
    BoxCollider2D* legHurtBox;
    BoxCollider2D* hitBox;
    float movementSpeed;
    bool faceRight;
    bool isAttacking;
    bool isAttackAnimFinished;
    bool isHurt = false;
    bool canHitConfirm;
    bool hitConfirmSuccess;

    void UpdateMovement(PlayerInput* input);
    void UpdateCMKCollider();
};

