#pragma once

#include <cmath>
#include <array>
#include <stdexcept>

#include "Vector3.h"

class Matrix4 {
private:
    float data[4][4];

public:
    Matrix4();

    /*float& operator()(int row, int col) {
        return data[row][col];
    }*/

    /*float operator()(int row, int col) const {
        return data[row][col];
    }*/


    // Multiplication: * Operator Overloads
    Matrix4 operator*(const Matrix4& other);
    Vector3 operator*(const Vector3& vec) const;

    // Matrix-specific functions
    void         updateElement(int row, int col, float value);
    float        getElement(int row, int col) const;
    const float* getData() const;

    // Transformation utilities based on matrix
    // For practicity, I added these in the Matrix API,
    // however, these might be better candidates for a Transform class
    // ... That's your homework!
    static Matrix4 translation(float tx, float ty, float tz);
    static Matrix4 scale(float sx, float sy, float sz);
    static Matrix4 rotationX(float angle);
    static Matrix4 rotationY(float angle);
    static Matrix4 rotationZ(float angle);
    static Matrix4 rotationXYZ(float x, float y, float z); // axis-angle based
    static Matrix4 identity();
    static Matrix4 orthographic(float left, float right,
        float bottom, float top, float near, float far);
    static Matrix4 perspective(float fov, float aspectRatio,
        float near, float far);
    static Matrix4 lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
    // I encourage to implement the Euler Angles formula: Removes the gimball lock problem


};