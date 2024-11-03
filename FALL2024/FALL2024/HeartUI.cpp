#include "HeartUI.h"

HeartUI::HeartUI(Mesh* mesh, GLint modelMatrixLoc, Renderer& renderer, Vector3 pos) : GameObject(mesh, modelMatrixLoc)
{
    Square* heart1Mesh = new Square(Vector3(0.0f, 0.0f, 1.0f), 0.5f, renderer.GetShader());
    heart1Mesh->AddTexture("heart.png", GL_RGBA);
    this->mesh = heart1Mesh;
    getTransform()->setPosition(pos);
}