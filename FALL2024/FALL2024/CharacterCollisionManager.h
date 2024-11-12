#pragma once
#include "BoxCollider2D.h"
#include "Renderer.h"
class CharacterCollisionManager
{
private:
    BoxCollider2D* hurtBox;
    BoxCollider2D* legHurtBox;
    BoxCollider2D* hitBox;
public:
    CharacterCollisionManager(Renderer& renderer, const Vector3& pos, const Vector3& scale);
    void initHitboxes(Renderer& renderer, const Vector3& pos, const Vector3& scale);
    BoxCollider2D* createBoxCollider(Renderer& renderer, const Vector3& pos, const Vector3& scale, const Vector3& color);
    void setupHitboxes(const Vector3& pos, int playerSide);
    BoxCollider2D* getHurtBox();
    BoxCollider2D* getLegHurtBox();
    BoxCollider2D* getHitBox();
    ~CharacterCollisionManager();
};

