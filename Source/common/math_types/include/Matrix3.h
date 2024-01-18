#ifndef MATRIX_3_H
#define MATRIX_3_H

#include "Vector3.h"
#include "Quaternion.h"
#include "TypeDefinitions.h"

// Holds a 3x3 row major matrix representing a transformation in 3D space that does
// not include a translational component.
class Matrix3
{
    public:
    Matrix3();
    Matrix3(real d0, real d1, real d2,
             real d3, real d4, real d5,
             real d6, real d7, real d8);

    // Holds the tensor matrix data in array form.
    real data[9];

    // Transform the given vector by this matrix.
    Vector3 operator*(const Vector3 &vector) const;

    Matrix3 operator*(const Matrix3 &other) const;

    // Multiplies this matrix in place by the given matrix.
    void operator*=(const Matrix3 &other);

    // Returns a new matrix containing the inverse of this matrix
    Matrix3 Inverse() const;

    // Inverts the matrix.
    void Invert();

    // Sets the matrix to be the inverse of the given matrix.
    void SetInverse(const Matrix3 &other);

    // Sets this matrix to be the rotation matrix corresponding to the given quaternion.
    // i.e. creates a rotation matrix from a quaternion.
    void SetOrientation(const Quaternion &quat);

    // Sets the matrix to be the transpose of the given matrix.
    void SetTranspose(const Matrix3 &other);

    // Transform the given vector by this matrix.
    Vector3 Transform(const Vector3 &vector) const;

    // Returns a new matrix containing th etranspose of this matrix.
    Matrix3 Transpose() const;
};

#endif //MATRIX_3_H