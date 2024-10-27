#pragma once
#include<iostream>
#include <glew/glew.h>
#include"Square.h"
#include"ObjectMesh.h"
class BoxCollider2D : public ObjectMesh
{
private:
    float x, y;         // Position (top-left corner)
    float width, height; // Dimensions
    Square* square;

public:
    // Constructor
    BoxCollider2D(Mesh* mesh, GLint modelMatrixLoc, Vector3 position, Vector3 scale);

    // Getters for position and size
    float getX();
    float getY();
    float getWidth();
    float getHeight();

    // Setters for position and size
    void setPosition(float xPos, float yPos);
    void setSize(float w, float h);

    // Method to check if this box is colliding with another box
    bool isColliding(BoxCollider2D& other);
};

