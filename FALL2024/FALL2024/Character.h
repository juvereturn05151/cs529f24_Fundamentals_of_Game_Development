#pragma once
#include "GameObject.h"
#include "PlayerInput.h"
#include "AnimatedSquare.h"
#include "BoxCollider2D.h"
#include "Renderer.h"
class Character : public GameObject
{
public:
    Character(Mesh* mesh, GLint modelMatrixLoc);
    Character(Mesh* mesh, GLint modelMatrixLoc, Renderer& renderer, int playerSide = 1);
    void setAnimatedSquare(AnimatedSquare* animated);
    void setFaceRight(bool isRight);

    void updateInput(PlayerInput* input);
    void update(float deltaTime) override;
    void cleanup() override;
    void draw() override;

    // Character actions (movement, etc.)
    void moveRight();
    void moveLeft();
    void attack();
    void triggerHurt();
    bool isAnimationFinished();
    void setHurtBox(BoxCollider2D* newHurtBox);
    BoxCollider2D* getHurtBox();
    BoxCollider2D* getLegHurtBox();
    BoxCollider2D* getHitBox();
    void setCanHitConfirm(bool isEnemyHurt);
    bool getCanHitConfirm();
    bool getHitConfirmSuccess();
    bool getIsHurt();
    void setYouWin(bool win);
    bool getYouWin();
    void setYouLose(bool lose);
    void reset();

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
    bool youWin;
    bool youLose;
    bool isBlocking;
    bool block;

    void updateMovement(PlayerInput* input);
    void updateCMKCollider();
    void checkForBlock(PlayerInput* input);
};

