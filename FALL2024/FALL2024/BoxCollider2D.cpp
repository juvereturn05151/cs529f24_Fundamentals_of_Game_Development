#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D(float xPos, float yPos, float w, float h)
    : x(xPos), y(yPos), width(w), height(h)
{

}

void BoxCollider2D::createRenderableSquare(Shader* shaderProgram)
{
    square = new Square(Vector3(x - width, y - height, 0), Vector3(x - width, y + height, 0),
        Vector3(x + width, y + height, 0), Vector3(x + width, y - height, 0), Vector3(0,1,0), 0.5f, shaderProgram);
}

// Getters for position and size
float BoxCollider2D::getX() const { return x; }
float BoxCollider2D::getY() const { return y; }
float BoxCollider2D::getWidth() const { return width; }
float BoxCollider2D::getHeight() const { return height; }

// Setters for position and size
void BoxCollider2D::setPosition(float xPos, float yPos) { x = xPos; y = yPos; }
void BoxCollider2D::setSize(float w, float h) { width = w; height = h; }

// Method to check if this box is colliding with another box
bool BoxCollider2D::isColliding(const BoxCollider2D& other) const {
    // Check for overlap on the x-axis
    bool collisionX = x + width >= other.getX() &&
        other.getX() + other.getWidth() >= x;

    // Check for overlap on the y-axis
    bool collisionY = y + height >= other.getY() &&
        other.getY() + other.getHeight() >= y;

    // If both axes overlap, there's a collision
    return collisionX && collisionY;
}

void BoxCollider2D::draw() 
{
    Matrix4<float> modelMatrix = getGlobalModelMatrix();
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix.getData());

    if (square != NULL)
    {
        square->draw();
    }
}

