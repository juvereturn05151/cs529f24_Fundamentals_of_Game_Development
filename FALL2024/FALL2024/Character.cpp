#include "Character.h"
#include "FrameController.h"
#include "InputManager.h"

Character::Character(Mesh* mesh, GLint modelMatrixLoc) : ObjectMesh(mesh, modelMatrixLoc)
{
    movementSpeed = 5.0f;
}

Character::Character(Mesh* mesh, GLint modelMatrixLoc, Renderer& renderer, int playerSide) : ObjectMesh(mesh, modelMatrixLoc)
{
    movementSpeed = 5.0f;

    AnimatedSquare* ryu = new AnimatedSquare(Vector3(0.0f, 0.0f, 1.0f), 0.5f, renderer.GetShader());
    ryu->AddTexture();
    Node* visualHolder = new ObjectMesh(ryu, renderer.GetModelMatrixLoc());
    
    if (playerSide == 0)
    {
        visualHolder->getTransform()->setScale(Vector3(3.5f, 3.5f, 3.5f));
    }
    else 
    {
        visualHolder->getTransform()->setScale(Vector3(-3.5f, 3.5f, 3.5f));
    }

    visualHolder->getTransform()->setPosition(Vector3(-0.5f, 0.0f, 0.0f));

    SetAnimatedSquare(ryu);

    Vector3 pos = getTransform()->getPosition();
    Vector3 scale = Vector3(Vector3(getTransform()->getScale().x / 1.75f, getTransform()->getScale().y, getTransform()->getScale().z));// getTransform()->getScale();


    //Square* squareMesh = new Square(Vector3(pos.x - scale.x, pos.y - scale.y, 0), Vector3(pos.x - scale.x, pos.y + scale.y, 0),
     //   Vector3(pos.x + scale.x, pos.y + scale.y, 0), Vector3(pos.x + scale.x, pos.y - scale.y, 0), Vector3(0, 1, 0), 0.5f, renderer.GetShader());

    BoxCollider2D* boxCollider = new BoxCollider2D(NULL, renderer.GetModelMatrixLoc(), pos, scale);

    setHurtBox(boxCollider);
    Node* hurtBoxHolder = getHurtBox();

    //Square* squareMesh2 = new Square(Vector3(pos.x - scale.x, pos.y - scale.y, 0), Vector3(pos.x - scale.x, pos.y + scale.y, 0),
       // Vector3(pos.x + scale.x, pos.y + scale.y, 0), Vector3(pos.x + scale.x, pos.y - scale.y, 0), Vector3(1, 0, 0), 0.5f, renderer.GetShader());

    hitBox = new BoxCollider2D(NULL, renderer.GetModelMatrixLoc(), pos, scale);

    if (playerSide == 0)
    {
        hurtBoxHolder->getTransform()->setPosition(Vector3(-3.0f, 0.0f, 0.0f));
        hurtBoxHolder->getTransform()->setScale(Vector3(1.0f, 2.0f, 1.0f));
        hitBox->getTransform()->setScale(Vector3(1.0f ,0.5f,1.0f));
        hitBox->getTransform()->setPosition(Vector3(-3.0f + 1.75f, -2.0f, 0.0f));
    }
    else
    {
        hurtBoxHolder->getTransform()->setPosition(Vector3(3.0f, 0.0f, 0.0f));
        hurtBoxHolder->getTransform()->setScale(Vector3(1.0f, 2.0f, 1.0f));
        hitBox->getTransform()->setScale(Vector3(1.0f, 0.5f, 1.0f));
        hitBox->getTransform()->setPosition(Vector3(3.0f - 1.75f, -2.0f, 0.0f));
    }

    hitBox->setIsActive(false);

    addChild(visualHolder);
    addChild(hurtBoxHolder);
    addChild(hitBox);

    addPhysicsComponent(1.0f);
}

void Character::setHurtBox(BoxCollider2D* newHurtBox)
{
    hurtBox = newHurtBox;
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
    if (animatedSquare != NULL)
    {
        animatedSquare->update_animation(deltaTime);
    }

    ObjectMesh::update(deltaTime);
}

void Character::draw()
{
    ObjectMesh::draw();
}

void Character::updateInput(PlayerInput* input) 
{
    if (isHurt) {
        if (animatedSquare != NULL) 
        {
            animatedSquare->set_animation(AnimationState::Hurt);
        }

        // Skip other updates while hurt
        if (IsAnimationFinished()) 
        {
            isHurt = false; // End hurt state once animation is done
        }
        return;
    }


    // Check if the character is attacking
    if (isAttacking)
    {
        if (animatedSquare != NULL)
        {
            animatedSquare->set_animation(AnimationState::cMK); 

            hitBox->setIsActive(animatedSquare->isAtFrame(3));
        }

        if (IsAnimationFinished()) 
        {

            isAttacking = false; // Reset attack state
        }

        // While attacking, skip movement updates
        return;
    }
    else
    {
        // Handle crouching medium kick input (cMK)
        if (InputManager::IsKeyJustPressed(input->GetcMK()))
        {
            
            Attack();
            // Prevent movement during the attack
            return;
        }

        // Apply the movement
        UpdateMovement(input);
    }
}

void Character::TriggerHurt() 
{
    

    isHurt = true;  // Set hurt state
    if (animatedSquare != NULL) 
    {
        animatedSquare->set_animation(AnimationState::Hurt);
    }
    hitBox->setIsActive(false); // Disable hitbox while in hurt state
}


void Character::UpdateMovement(PlayerInput* input)
{
    deltaX = 0.0f, deltaY = 0.0f;
    // Handle left/right movement
    if (InputManager::IsKeyPressed(input->GetMoveRight())) {
        MoveRight();
    }
    if (InputManager::IsKeyPressed(input->GetMoveLeft())) {
        MoveLeft();
    }

    if (deltaX == 0.0f && deltaY == 0.0f)
    {
        if (animatedSquare != NULL)
        {
            animatedSquare->set_animation(AnimationState::Idle);
        }
    }

    getTransform()->setPosition(getTransform()->getPosition() + Vector3(deltaX, deltaY, 0));
}

void Character::MoveRight()
{
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

void Character::MoveLeft()
{
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

void Character::Attack() 
{
    isAttacking = true; // Set attacking state
    if (animatedSquare != NULL)
    {
        animatedSquare->set_animation(AnimationState::cMK); // Set cMK animation
    }
}

void Character::SetFaceRight(bool isRight)
{
    faceRight = isRight;
}

bool Character::IsAnimationFinished()
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

BoxCollider2D* Character::getHitBox()
{
    return hitBox;
}