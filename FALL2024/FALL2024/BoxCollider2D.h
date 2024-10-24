#pragma once
#include<iostream>
#include <glew/glew.h>
#include"Square.h"
#include"Node.h"
class BoxCollider2D : public Node
{
private:
    float x, y;         // Position (top-left corner)
    float width, height; // Dimensions
    Square* square;

public:
    // Constructor
    BoxCollider2D(float xPos, float yPos, float w, float h);

    // Getters for position and size
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    // Setters for position and size
    void setPosition(float xPos, float yPos);
    void setSize(float w, float h);

    // Method to check if this box is colliding with another box
    bool isColliding(const BoxCollider2D& other) const;

    void createRenderableSquare(Shader* shaderProgram);

    void draw()override;
};

