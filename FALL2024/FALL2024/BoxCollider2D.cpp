#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D(Mesh* mesh, GLint modelMatrixLoc, Vector3 position, Vector3 scale)
    : GameObject(mesh, modelMatrixLoc), x(position.x), y(position.y), width(scale.x * 2.0f), height(scale.y)
{
    isActive = true;
}

// Getters for position and size
float BoxCollider2D::getX() 
{ 
    Matrix4<float> globalMatrix = getGlobalModelMatrix();
    return globalMatrix.getElement(3,0);
}

float BoxCollider2D::getY() 
{ 
    Matrix4<float> globalMatrix = getGlobalModelMatrix();
    return globalMatrix.getElement(3, 1);
}

float BoxCollider2D::getWidth() 
{ 
    Matrix4<float> globalMatrix = getGlobalModelMatrix();
    return (width) * globalMatrix.getElement(0, 0) ;
}
float BoxCollider2D::getHeight() 
{ 
    Matrix4<float> globalMatrix = getGlobalModelMatrix();
    return (height * 2.0f) * globalMatrix.getElement(1, 1);
}

// Setters for position and size
void BoxCollider2D::setPosition(float xPos, float yPos) 
{ 
    x = xPos; 
    y = yPos; 
}
void BoxCollider2D::setSize(float w, float h) { width = w; height = h; }

// Method to check if this box is colliding with another box
bool BoxCollider2D::isColliding(BoxCollider2D& other) 
{
    if (!other.getIsActive())
    {
        return false;
    }

    if (!isActive)
    {
        return false;
    }

    x = getX();
    y = getY();
    width = getWidth();
    height = getHeight();

    /*std::cout << "x + width: " << x + width << " other.getX(): " << other.getX() << std::endl;
    std::cout << "other.getX() + other.getWidth() : " << other.getX() + other.getWidth() << " x : " << x << std::endl;

    std::cout << "y + height: " << y + height << " other.getY(): " << other.getY() << std::endl;
    std::cout << "other.getY() + other.getHeight() : " << other.getY() + other.getHeight() << " y : " << y << std::endl;*/

    // Check for overlap on the x-axis
    bool collisionX = x + width >= other.getX() &&
        other.getX() + other.getWidth() >= x;

    // Check for overlap on the y-axis
    bool collisionY = y + height >= other.getY() &&
        other.getY() + other.getHeight() >= y;

    // If both axes overlap, there's a collision
    return collisionX && collisionY;
}

