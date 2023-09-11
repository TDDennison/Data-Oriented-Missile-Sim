#ifndef MATRIX_3_H
#define MATRIX_3_H

#include "Vector3.h"
#include "Quaternion.h"
#include "../Core/TypeDefinitions.h"

// Holds a 3x3 row major matrix representing a transformation in 3D space that does
// not include a translational component.
class Matrix3
{
    public:
    Matrix3(): data{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} {}
    Matrix3(real d0, real d1, real d2,
             real d3, real d4, real d5,
             real d6, real d7, real d8) : 
             data{d0, d1, d2, d3, d4, d5, d6, d7, d8} {}

    // Holds the tensor matrix data in array form.
    real data[9];

    // Transform the given vector by this matrix.
    Vector3 operator*(const Vector3 &vector) const
    {
        return Vector3(vector.x * data[0] + vector.y * data[1] + vector.z * data[2],
                       vector.x * data[3] + vector.y * data[4] + vector.z * data[5],
                       vector.x * data[6] + vector.y * data[7] + vector.z * data[8]);
    }

    Matrix3 operator*(const Matrix3 &other) const
    {
        return Matrix3(
            // Row 1
            data[0] * other.data[0] + data[1] * other.data[3] + data[2] * other.data[6],
            data[0] * other.data[1] + data[1] * other.data[4] + data[2] * other.data[7],
            data[0] * other.data[2] + data[1] * other.data[5] + data[2] * other.data[8],

            // Row 2
            data[3] * other.data[0] + data[4] * other.data[3] + data[5] * other.data[6],
            data[3] * other.data[1] + data[4] * other.data[4] + data[5] * other.data[7],
            data[3] * other.data[2] + data[4] * other.data[5] + data[5] * other.data[8],

            // Row 3
            data[6] * other.data[0] + data[7] * other.data[3] + data[8] * other.data[6],
            data[6] * other.data[1] + data[7] * other.data[4] + data[8] * other.data[7],
            data[6] * other.data[2] + data[7] * other.data[5] + data[8] * other.data[8]
        );
    }

    // Multiplies this matrix in place by the given matrix.
    void operator*=(const Matrix3 &other)
    {
        real t1;
        real t2;
        real t3;

        // Row 1
        t1 = data[0] * other.data[0] + data[1] * other.data[3] + data[2] * other.data[6];
        t2 = data[0] * other.data[1] + data[1] * other.data[4] + data[2] * other.data[7];
        t3 = data[0] * other.data[2] + data[1] * other.data[5] + data[2] * other.data[8];
        data[0] = t1;
        data[1] = t2;
        data[2] = t3;

        // Row 2
        t1 = data[3] * other.data[0] + data[4] * other.data[3] + data[5] * other.data[6];
        t2 = data[3] * other.data[1] + data[4] * other.data[4] + data[5] * other.data[7];
        t3 = data[3] * other.data[2] + data[4] * other.data[5] + data[5] * other.data[8];
        data[3] = t1;
        data[4] = t2;
        data[5] = t3;

        // Row 3
        t1 = data[6] * other.data[0] + data[7] * other.data[3] + data[8] * other.data[6];
        t2 = data[6] * other.data[1] + data[7] * other.data[4] + data[8] * other.data[7];
        t3 = data[6] * other.data[2] + data[7] * other.data[5] + data[8] * other.data[8];
        data[6] = t1;
        data[7] = t2;
        data[8] = t3;
    }

    // Returns a new matrix containing the inverse of this matrix
    Matrix3 Inverse() const
    {
        Matrix3 result;
        result.SetInverse(*this);
        return result;
    }

    // Inverts the matrix.
    void Invert()
    {
        SetInverse(*this);
    }

    // Sets the matrix to be the inverse of the given matrix.
    void SetInverse(const Matrix3 &other)
    {
        real t1 = other.data[0] * other.data[4];
        real t2 = other.data[0] * other.data[5];
        real t3 = other.data[1] * other.data[3];
        real t4 = other.data[2] * other.data[3];
        real t5 = other.data[1] * other.data[6];
        real t6 = other.data[2] * other.data[6];

        // Calculate the determinant.
        real det = (t1 * other.data[8] - t2 * other.data[7] - t3 * other.data[8] +
                     t4 * other.data[7] - t5 * other.data[5] - t6 * other.data[4]);

        // Make sure the determinant is non-zero.
        if (det == 0.0) return; // Or throw an error.

        real invDet = 1.0 / det;

        data[0] =  (other.data[4] * other.data[8] - other.data[5] * other.data[7]) * invDet;
        data[1] = -(other.data[1] * other.data[8] - other.data[2] * other.data[7]) * invDet;
        data[2] =  (other.data[1] * other.data[5] - other.data[2] * other.data[4]) * invDet;
        data[3] = -(other.data[3] * other.data[8] - other.data[5] * other.data[6]) * invDet;
        data[4] =  (other.data[0] * other.data[8] - t6) * invDet;
        data[5] = -(t2 - t4) * invDet;
        data[6] =  (other.data[3] * other.data[7] - other.data[4] * other.data[6]) * invDet;
        data[7] = -(other.data[0] * other.data[7] - t5) * invDet;
        data[8] =  (t1 - t3) * invDet;
    }

    // Sets this matrix to be the rotation matrix corresponding to the given quaternion.
    // i.e. creates a rotation matrix from a quaternion.
    void SetOrientation(const Quaternion &quat)
    {
        real ii = quat.i * quat.i;
        real jj = quat.j * quat.j;
        real kk = quat.k * quat.k;

        real ij = quat.i * quat.j;
        real ik = quat.i * quat.k;
        real iw = quat.i * quat.w;

        real jk = quat.j * quat.k;
        real jw = quat.j * quat.w;

        real kw = quat.k * quat.w;

        data[0] = 1 - (2 * jj + 2 * kk);
        data[1] = (2 * ij) + (2 * kw);
        data[2] = (2 * ik) - (2 * jw);
        data[3] = (2 * ij) - (2 * kw);
        data[4] = 1 - (2 * ii + 2 * kk);
        data[5] = (2 * jk) + (2 * iw);
        data[6] = (2 * ik) + (2 * jw);
        data[7] = (2 * jk) - (2 * iw);
        data[8] = 1 - (2 * ii + 2 * jj);
    }

    // Sets the matrix to be the transpose of the given matrix.
    void SetTranspose(const Matrix3 &other)
    {
        data[0] = other.data[0];
        data[1] = other.data[3];
        data[2] = other.data[6];
        data[3] = other.data[1];
        data[4] = other.data[4];
        data[5] = other.data[7];
        data[6] = other.data[2];
        data[7] = other.data[5];
        data[8] = other.data[8];
    }

    // Transform the given vector by this matrix.
    Vector3 Transform(const Vector3 &vector) const
    {
        return (*this) * vector;
    }

    // Returns a new matrix containing th etranspose of this matrix.
    Matrix3 Transpose() const
    {
        Matrix3 result;
        result.SetTranspose(*this);
        return result;
    }
};

#endif //MATRIX_3_H