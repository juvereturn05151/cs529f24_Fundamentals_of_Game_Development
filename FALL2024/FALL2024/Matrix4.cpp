#include "Matrix4.h"

Matrix4::Matrix4()
{
	// Write implementation here
    int identity[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            data[i][j] = identity[i][j];
        }
    }
}

void Matrix4::updateElement(int row, int col, float value)
{
	// Write implementation here
    data[row][col] = value;
}

float Matrix4::getElement(int row, int col) const
{
    // Write implementation here
    return data[row][col];
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
    Matrix4 result_Matrix;
    // Write implementation here
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < matrix_size; ++k) {
                sum += data[i][k] * other.data[k][j];
            }
            result_Matrix.updateElement(i, j, sum);
        }
    }

    return result_Matrix;
}

Vector3 Matrix4::operator*(const Vector3& vec) const
{
	float x,y,z;
    // Write implementation here
    x = data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z + data[0][3];
    y = data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z + data[1][3];
    z = data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z + data[2][3];
    return Vector3(x, y, z);
}

Matrix4 Matrix4::translation(float tx, float ty, float tz)
{
    Matrix4 result;
    // Write implementation here
    result.updateElement(0, 3, tx);
    result.updateElement(1, 3, ty);
    result.updateElement(2, 3, tz);

    return result;
}

Matrix4 Matrix4::scale(float sx, float sy, float sz)
{
    Matrix4 result;
    // Write implementation here
    result.updateElement(0, 0, sx);
    result.updateElement(1, 1, sy);
    result.updateElement(2, 2, sz);
    return result;
}

Matrix4 Matrix4::rotationX(float angle)
{
    Matrix4 result;
    // Write implementation here
    float rad = angle;
    float cosA = cos(rad);
    float sinA = sin(rad);

    result.updateElement(0, 0, 1);
    result.updateElement(1, 1, cosA);
    result.updateElement(1, 2, -sinA);
    result.updateElement(2, 1, sinA);
    result.updateElement(2, 2, cosA);
    result.updateElement(3, 3, 1);
    return result;
}

Matrix4 Matrix4::rotationY(float angle)
{
    Matrix4 result;
    // Write implementation here
    float rad = angle; 
    float cosA = cos(rad);
    float sinA = sin(rad);

    result.updateElement(0, 0, cosA);
    result.updateElement(0, 2, sinA);
    result.updateElement(1, 1, 1);
    result.updateElement(2, 0, -sinA);
    result.updateElement(2, 2, cosA);
    result.updateElement(3, 3, 1);
    return result;
}

Matrix4 Matrix4::rotationZ(float angle)
{
    Matrix4 result;
    // Write implementation here
    float rad = angle; 
    float cosA = cos(rad);
    float sinA = sin(rad);

    result.updateElement(0, 0, cosA);
    result.updateElement(0, 1, -sinA);
    result.updateElement(1, 0, sinA);
    result.updateElement(1, 1, cosA);
    result.updateElement(2, 2, 1);
    result.updateElement(3, 3, 1);
    return result;
}