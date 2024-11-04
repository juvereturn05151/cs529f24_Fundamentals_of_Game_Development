#pragma once
#include<iostream>
#include <glew/glew.h>
#include"Square.h"
#include"GameObject.h"
class BoxCollider2D : public GameObject
{
private:
    float x, y;         // Position (top-left corner)
    float width, height; // Dimensions
    float widthJitterScale = 2.0f;
    float heightJitterScale = 2.0f;
    bool isDrawingActive;
    Square* square;

public:
    // Constructor
    BoxCollider2D(Mesh* mesh, GLint modelMatrixLoc, Vector3 position, Vector3 scale);

    // Getters for position and size
    float getX();
    float getY();
    float getWidth();
    float getHeight();

    void draw() override;

    // Setters for position and size
    void setPosition(float xPos, float yPos);
    void setSize(float w, float h);
    void setIsDrawingActive(bool active);

    // Method to check if this box is colliding with another box
    bool isColliding(BoxCollider2D& other);
};

