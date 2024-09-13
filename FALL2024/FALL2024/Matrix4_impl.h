#include "Matrix4.h"

template <typename T>
Matrix4<T>::Matrix4()
{
    T one = static_cast<T>(1);
    T zero = static_cast<T>(0);

    T identity[4][4] = {
        {one, zero, zero, zero},
        {zero, one, zero, zero},
        {zero, zero, one, zero},
        {zero, zero, zero, one}
    };

    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            data[i][j] = identity[i][j];
        }
    }
}

template <typename T>
void Matrix4<T>::updateElement(int row, int col, T value)
{
    if (row >= matrix_size || col >= matrix_size || row < 0 || col < 0) {
        throw std::out_of_range("Matrix indices are out of range");
    }

    data[row][col] = value;
}

template <typename T>
T Matrix4<T>::getElement(int row, int col) const
{
    if (row >= matrix_size || col >= matrix_size || row < 0 || col < 0) {
        throw std::out_of_range("Matrix indices are out of range");
    }

    return data[row][col];
}

template <typename T>
Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& other)
{
    Matrix4<T> result_Matrix;
    // Write implementation here
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            T sum = 0.0;
            for (int k = 0; k < matrix_size; ++k) {
                sum += data[i][k] * other.data[k][j];
            }
            result_Matrix.updateElement(i, j, sum);
        }
    }

    return result_Matrix;
}

template <typename T>
Vector3 Matrix4<T>::operator*(const Vector3& vec) const
{
    float x, y, z;
    // Write implementation here
    x = data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z + data[0][3];
    y = data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z + data[1][3];
    z = data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z + data[2][3];
    return Vector3(x, y, z);
}

template <typename T>
Matrix4<T> Matrix4<T>::translation(T tx, T ty, T tz)
{
    Matrix4 result;
    // Write implementation here
    result.updateElement(0, 3, tx);
    result.updateElement(1, 3, ty);
    result.updateElement(2, 3, tz);

    return result;
}

template <typename T>
Matrix4<T> Matrix4<T>::scale(T sx, T sy, T sz)
{
    Matrix4 result;
    // Write implementation here
    result.updateElement(0, 0, sx);
    result.updateElement(1, 1, sy);
    result.updateElement(2, 2, sz);
    return result;
}

template <typename T>
Matrix4<T> Matrix4<T>::rotationX(T angle)
{
    Matrix4 result;
    // Write implementation here
    T cosA = cos(angle);
    T sinA = sin(angle);

    result.updateElement(0, 0, 1);
    result.updateElement(1, 1, cosA);
    result.updateElement(1, 2, -sinA);
    result.updateElement(2, 1, sinA);
    result.updateElement(2, 2, cosA);
    result.updateElement(3, 3, 1);
    return result;
}

template <typename T>
Matrix4<T> Matrix4<T>::rotationY(T angle)
{
    Matrix4 result;
    // Write implementation here
    T cosA = cos(angle);
    T sinA = sin(angle);

    result.updateElement(0, 0, cosA);
    result.updateElement(0, 2, sinA);
    result.updateElement(1, 1, 1);
    result.updateElement(2, 0, -sinA);
    result.updateElement(2, 2, cosA);
    result.updateElement(3, 3, 1);
    return result;
}

template <typename T>
Matrix4<T> Matrix4<T>::rotationZ(T angle)
{
    Matrix4 result;
    // Write implementation here
    T cosA = cos(angle);
    T sinA = sin(angle);

    result.updateElement(0, 0, cosA);
    result.updateElement(0, 1, -sinA);
    result.updateElement(1, 0, sinA);
    result.updateElement(1, 1, cosA);
    result.updateElement(2, 2, 1);
    result.updateElement(3, 3, 1);
    return result;
}

template <typename T>
Matrix4<T> Matrix4<T>::perspective(T fovY, T aspect, T nearPlane, T farPlane)
{
    Matrix4 result;
    T zero = static_cast<T>(0);
    T one = static_cast<T>(1);
    T two = static_cast<T>(2);
    T tanHalfFovY = tan(fovY / two);
    T range = nearPlane - farPlane;

    result.updateElement(0, 0, one / (aspect * tanHalfFovY));
    result.updateElement(1, 1, one / tanHalfFovY);
    result.updateElement(2, 2, (nearPlane + farPlane) / range);
    result.updateElement(2, 3, two * nearPlane * farPlane / range);
    result.updateElement(3, 2, -one);
    result.updateElement(3, 3, zero);

    return result;
}

template <typename T>
Matrix4<T> Matrix4<T>::orthographic(T left, T right, T bottom, T top, T nearPlane, T farPlane)
{
    Matrix4 result;
    T one = static_cast<T>(1);
    T two = static_cast<T>(2);

    // Calculate the scale and translation factors
    T invRL = 1.0f / (right - left);
    T invTB = 1.0f / (top - bottom);
    T invNF = 1.0f / (farPlane - nearPlane);

    result.updateElement(0, 0, two * invRL);
    result.updateElement(1, 1, two * invTB);
    result.updateElement(2, 2, -two * invNF);
    result.updateElement(0, 3, -(right + left) * invRL);
    result.updateElement(1, 3, -(top + bottom) * invTB);
    result.updateElement(2, 3, -(farPlane + nearPlane) * invNF);
    result.updateElement(3, 3, one);

    return result;
}