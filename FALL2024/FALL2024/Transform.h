#pragma once
#include "Vector3.h"
#include "Matrix4.h"

/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Description: Transform component containing position, rotation, and scale of an object.
             This class is used to define the transformation properties of a node in a scene.
*/

class Transform
{
private:
    // The position of the object in 3D space
    Vector3 position;

    // The rotation of the object (in degrees or radians) around each axis
    Vector3 rotation;

    // The scale of the object in 3D space, affecting its size
    Vector3 scale;

public:
    // Constructor: Initializes the position, rotation, and scale to default values
    Transform();

    // Destructor: Cleans up any resources (if needed)
    ~Transform();

    // Sets the position of the object
    void setPosition(const Vector3& position);

    // Retrieves the current position of the object
    Vector3 getPosition() const;

    // Sets the rotation of the object
    void setRotation(const Vector3& rotation);

    // Retrieves the current rotation of the object
    Vector3 getRotation() const;

    // Sets the scale of the object
    void setScale(const Vector3& scale);

    // Retrieves the current scale of the object
    Vector3 getScale() const;

    // Returns the model matrix that combines position, rotation, and scale for this object
    Matrix4<float> getModelMatrix() const;

    // Translates (moves) the object by a certain amount in 3D space
    void translate(const Vector3& translateAmount);
};