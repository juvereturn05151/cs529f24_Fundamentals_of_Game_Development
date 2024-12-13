/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Description: A 2D Axis-Aligned Bounding Box (AABB) collider class for collision detection and debugging visualization.
*/

#pragma once
#include <iostream>
#include <glew/glew.h>
#include "Square.h"
#include "GameObject.h"

class BoxCollider2D : public GameObject {
private:
    float x, y;         // Top-left corner position
    float width, height; // Box dimensions
    float widthJitterScale = 2.0f; // Debugging scale factor for width
    float heightJitterScale = 2.0f; // Debugging scale factor for height
    bool isDrawingActive; // Toggle for visual representation
    Square* square;       // Used for rendering the box

public:
    // Constructor to initialize the box collider
    BoxCollider2D(Mesh* mesh, GLint modelMatrixLoc, Vector3 position, Vector3 scale);

    // Getters for box position and size
    float getX();
    float getY();
    float getWidth();
    float getHeight();

    // Render the box collider if drawing is active
    void draw() override;

    // Setters for position, size, and drawing toggle
    void setPosition(float xPos, float yPos);
    void setSize(float w, float h);
    void setIsDrawingActive(bool active);

    // Check collision with another box collider
    bool isColliding(BoxCollider2D& other);
};