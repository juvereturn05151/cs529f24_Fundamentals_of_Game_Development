#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D(Mesh* mesh, GLint modelMatrixLoc, Vector3 position, Vector3 scale)
    : ObjectMesh(mesh, modelMatrixLoc), x(position.x), y(position.y), width(scale.x), height(scale.y)
{

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
    return width * globalMatrix.getElement(0, 0);
}
float BoxCollider2D::getHeight() 
{ 
    Matrix4<float> globalMatrix = getGlobalModelMatrix();
    return height * globalMatrix.getElement(1, 1);
}

// Setters for position and size
void BoxCollider2D::setPosition(float xPos, float yPos) { x = xPos; y = yPos; }
void BoxCollider2D::setSize(float w, float h) { width = w; height = h; }

// Method to check if this box is colliding with another box
bool BoxCollider2D::isColliding(BoxCollider2D& other) 
{
    x = getX();
    y = getY();
    width = getWidth();
    height = getHeight();

    /*std::cout << "p1 posX: " << x << " p1 posY: " << y << std::endl;
    std::cout << "p1 width: " << width << " p1 height: " << height << std::endl;
    std::cout << "p2 posX: " << other.getX() << " p2 posY: " << other.getY() << std::endl;
    std::cout << "p2 width: " << other.getWidth() << " p2 height: " << other.getHeight() << std::endl;*/

    // Check for overlap on the x-axis
    bool collisionX = x + width >= other.getX() &&
        other.getX() + other.getWidth() >= x;

    // Check for overlap on the y-axis
    bool collisionY = y + height >= other.getY() &&
        other.getY() + other.getHeight() >= y;

    // If both axes overlap, there's a collision
    return collisionX && collisionY;
}

