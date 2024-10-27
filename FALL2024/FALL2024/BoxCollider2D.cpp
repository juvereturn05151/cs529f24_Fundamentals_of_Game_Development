#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D(Mesh* mesh, GLint modelMatrixLoc, Vector3 position, Vector3 scale)
    : ObjectMesh(mesh, modelMatrixLoc), x(position.x), y(position.y), width(scale.x), height(scale.y)
{

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

