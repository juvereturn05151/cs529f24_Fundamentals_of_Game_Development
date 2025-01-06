#include "CharacterCollisionManager.h"

CharacterCollisionManager::CharacterCollisionManager(Renderer& renderer, const Vector3& pos, const Vector3& scale)
{
    initHitboxes(renderer, pos, scale);
}

CharacterCollisionManager::~CharacterCollisionManager()
{
    if (hitBox != NULL)
    {
        delete hitBox;
    }

    if (hurtBox != NULL)
    {
        delete hurtBox;
    }

    if (legHurtBox != NULL)
    {
        delete legHurtBox;
    }
}


BoxCollider2D* CharacterCollisionManager::getHitBox()
{
    return hitBox;
}

BoxCollider2D* CharacterCollisionManager::getHurtBox()
{
    return hurtBox;
}

BoxCollider2D* CharacterCollisionManager::getLegHurtBox()
{
    return legHurtBox;
}

void CharacterCollisionManager::initHitboxes(Renderer& renderer, const Vector3& pos, const Vector3& scale)
{
    hitBox = createBoxCollider(renderer, pos, scale, Vector3(1, 0, 0));
    hurtBox = createBoxCollider(renderer, pos, scale, Vector3(0, 1, 0));
    legHurtBox = createBoxCollider(renderer, pos, scale, Vector3(0, 1, 0));
}

BoxCollider2D* CharacterCollisionManager::createBoxCollider(Renderer& renderer, const Vector3& pos, const Vector3& scale, const Vector3& color)
{
    Square* squareMesh = new Square(Vector3(pos.x - scale.x, pos.y - scale.y, 0),
        Vector3(pos.x - scale.x, pos.y + scale.y, 0),
        Vector3(pos.x + scale.x, pos.y + scale.y, 0),
        Vector3(pos.x + scale.x, pos.y - scale.y, 0),
        color, 0.5f, renderer.GetShader());
    return new BoxCollider2D(squareMesh, renderer.GetModelMatrixLoc(), pos, scale);
}

void CharacterCollisionManager::setupHitboxes(const Vector3& pos, int playerSide)
{
    if (playerSide == 0)
    {
        Vector3 centerPos = pos - Vector3(0.5f, 0.0f, 0.0f);
        hurtBox->getTransform()->setPosition(Vector3(centerPos.x,0.0f,0.0f));
        hurtBox->getTransform()->setScale(Vector3(1.0f, 2.0f, 1.0f));
        hitBox->getTransform()->setScale(Vector3(1.0f, 0.5f, 1.0f));
        hitBox->getTransform()->setPosition(Vector3(centerPos.x + 1.75f, -2.0f, 0.0f));
        legHurtBox->getTransform()->setScale(Vector3(0.75f, 0.5f, 1.0f));
        legHurtBox->getTransform()->setPosition(Vector3(centerPos.x + 0.75f, -2.0f, 0.0f));
    }
    else
    {
        Vector3 centerPos = pos + Vector3(0.5f, 0.0f, 0.0f);
        hurtBox->getTransform()->setPosition(Vector3(centerPos.x, 0.0f, 0.0f));
        hurtBox->getTransform()->setScale(Vector3(1.0f, 2.0f, 1.0f));
        hitBox->getTransform()->setScale(Vector3(1.0f, 0.5f, 1.0f));
        hitBox->getTransform()->setPosition(Vector3(centerPos.x - 1.75f, -2.0f, 0.0f));
        legHurtBox->getTransform()->setScale(Vector3(0.75f, 0.5f, 1.0f));
        legHurtBox->getTransform()->setPosition(Vector3(centerPos.x - 0.75f, -2.0f, 0.0f));
    }

    //For Displaying Collisions
    hitBox->setIsDrawingActive(true);
    hurtBox->setIsDrawingActive(true);
    legHurtBox->setIsDrawingActive(true);

    hitBox->setIsActive(false);
    legHurtBox->setIsActive(false);
}

void CharacterCollisionManager::updateLegHitBox(AnimatedCharacter* animatedCharacter, int playerSide)
{
    if (legHurtBox != NULL)
    {
        float sign = 1.0f;

        if (playerSide == 0)
        {
            sign = -1.0f;
        }
        else
        {
            sign = 1.0f;
        }

        Vector3 centerPos = legHurtBox->getTransform()->getPosition();

        if (animatedCharacter->isAtFrame(2) || animatedCharacter->isAtFrame(5))
        {
            legHurtBox->getTransform()->setScale(Vector3(0.75f, 0.5f, 1.0f));
            legHurtBox->getTransform()->setPosition(Vector3((sign * 0.25f), centerPos.y, 0));
        }
        else if (animatedCharacter->isAtFrame(3) || animatedCharacter->isAtFrame(4))
        {
            legHurtBox->getTransform()->setScale(Vector3(1.8f, 0.5f, 1.0f));
            legHurtBox->getTransform()->setPosition(Vector3((sign * -0.1f), centerPos.y, 0));
        }
        else
        {
            legHurtBox->getTransform()->setScale(Vector3(0.25f, 0.5f, 1.0f));
            legHurtBox->getTransform()->setPosition(Vector3((sign * 2.0f), centerPos.y, 0));
        }
    }
}