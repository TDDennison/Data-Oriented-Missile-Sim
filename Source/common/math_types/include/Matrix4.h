#ifndef MATRIX_4_H
#define MATRIX_4_H

#include "Vector3.h"
#include "Quaternion.h"
#include "TypeDefinitions.h"

// Holds a transform matrix, consisting of a rotation matrix and a position.
// The matrix has 12 elements, and is assumed that the remaining four are (0,0,0,1)
// to produce a homegenous matrix.
// The rotation matrix consists of a 3x3 matrix occupying the left-most three columns
// of the 3x4 matrix.
// The last column contains the positional data.

class Matrix4
{
    public:

    // Holds the transform matrix data in array form.
    real data[16]{0.0};

    // Transform the given vector by this matrix.
    Vector3 operator*(const Vector3 &vector) const;

    // Returns a matrix, which is this one multiplied by the given matrix.
    Matrix4 operator*(const Matrix4 &other) const;

    // Returns the determinant of the matrix.
    real GetDeterminant() const;

    // Returns a new matrix containing the inverse of this matrix.
    Matrix4 Inverse() const;

    // Inverts this matrix.
    void Invert();

    // Sets the matrix to be the inverse of the given matrix.
    void SetInverse(const Matrix4 &other);

    // Sets this matrix to be the rotation matrix corresponding to the given quaternion.
    void SetOrientationAndPosition(const Quaternion &quat, const Vector3 &pos);

    // Transform the given vector by this matrix.
    Vector3 Transform(const Vector3 &vector) const;

    // Transform the given direction vector by this matrix.
    Vector3 TransformDirection(const Vector3 &vector) const;

    // Transform the given vector by the transormational inverse of this matrix.
    Vector3 TransformInverse(const Vector3 &vector) const;

    // Transform the given direciton vector by the transformational inverse of this matrix.
    Vector3 TransformInverseDirection(const Vector3 &vector) const;
};

#endif //MATRIX_4_H