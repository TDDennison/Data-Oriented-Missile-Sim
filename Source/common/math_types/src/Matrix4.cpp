#include "Matrix4.h"

// Transform the given vector by this matrix.
Vector3 Matrix4::operator*(const Vector3 &vector) const
{
    return Vector3(vector.x * data[0] + vector.y * data[1] + vector.z * data[2] + data[3],
                    vector.x * data[4] + vector.y * data[5] + vector.z * data[6] + data[7],
                    vector.x * data[8] + vector.y * data[9] + vector.z * data[10] + data[11]);
}

// Returns a matrix, which is this one multiplied by the given matrix.
Matrix4 Matrix4::operator*(const Matrix4 &other) const
{
    Matrix4 result;

    // Column 1
    result.data[0] = other.data[0] * data[0] + other.data[4] * data[1] + other.data[8] * data[2];
    result.data[4] = other.data[0] * data[4] + other.data[4] * data[5] + other.data[8] * data[6];
    result.data[8] = other.data[0] * data[8] + other.data[4] * data[9] + other.data[8] * data[10];

    // Column 2
    result.data[1] = other.data[1] * data[0] + other.data[5] * data[1] + other.data[9] * data[2];
    result.data[5] = other.data[1] * data[4] + other.data[5] * data[5] + other.data[9] * data[6];
    result.data[9] = other.data[1] * data[8] + other.data[5] * data[9] + other.data[9] * data[10];

    // Column 3
    result.data[2]  = other.data[2] * data[0] + other.data[6] * data[1] + other.data[10] * data[2];
    result.data[6]  = other.data[2] * data[4] + other.data[6] * data[5] + other.data[10] * data[6];
    result.data[10] = other.data[2] * data[8] + other.data[6] * data[9] + other.data[10] * data[10];

    // Column 4
    result.data[3]  = other.data[3] * data[0] + other.data[7] * data[1] + other.data[11] * data[2]  + data[3];
    result.data[7]  = other.data[3] * data[4] + other.data[7] * data[5] + other.data[11] * data[6]  + data[7];
    result.data[11] = other.data[3] * data[8] + other.data[7] * data[9] + other.data[11] * data[10] + data[11];

    return result;
}

// Returns the determinant of the matrix.
real Matrix4::GetDeterminant() const
{
    return data[8] * data[5] * data[2] +
        data[4] * data[9] * data[2] +
        data[8] * data[1] * data[6] -
        data[0] * data[9] * data[6] -
        data[4] * data[1] * data[10] +
        data[0] * data[5] * data[10];
}

// Returns a new matrix containing the inverse of this matrix.
Matrix4 Matrix4::Inverse() const
{
    Matrix4 result;
    result.SetInverse(*this);
    return result;
}

// Inverts this matrix.
void Matrix4::Invert()
{
    SetInverse(*this);
}

// Sets the matrix to be the inverse of the given matrix.
void Matrix4::SetInverse(const Matrix4 &other)
{
    // Make sure the determinant is non-zero.
    real det = GetDeterminant();
    if (det == 0.0) return;
    real invDet = 1.0 / det;

    // Column 1
    data[0] = (-other.data[9] * other.data[6] + other.data[5] * other.data[10]) * invDet;
    data[4] =  (other.data[8] * other.data[6] - other.data[4] * other.data[10]) * invDet;
    data[8] = (-other.data[8] * other.data[5] + other.data[4] * other.data[9] * other.data[15]) * invDet;

    // Column 2
    data[1] =  (other.data[9] * other.data[2] - other.data[1] * other.data[10]) * invDet;
    data[5] = (-other.data[8] * other.data[2] + other.data[0] * other.data[10]) * invDet;
    data[9] =  (other.data[8] * other.data[1] - other.data[0] * other.data[9] * other.data[15]) * invDet;

    // Column 3
    data[2] =  (-other.data[5] * other.data[2] + other.data[6] * other.data[15]) * invDet;
    data[6] =   (other.data[4] * other.data[2] - other.data[6] * other.data[15]) * invDet;
    data[10] = (-other.data[4] * other.data[1] + other.data[5] * other.data[15]) * invDet;

    // Column 4
    data[3]  =  (  other.data[9] * other.data[6]  * other.data[3]  
                    - other.data[5] * other.data[10] * other.data[3]  
                    - other.data[9] * other.data[2]  * other.data[7] 
                    + other.data[1] * other.data[10] * other.data[7] 
                    + other.data[5] * other.data[2]  * other.data[11]
                    - other.data[1] * other.data[6]  * other.data[11] ) * invDet;


    data[7]  =  ( - other.data[8] * other.data[6]  * other.data[3]  
                    + other.data[4] * other.data[10] * other.data[3]  
                    + other.data[8] * other.data[2]  * other.data[7] 
                    - other.data[0] * other.data[10] * other.data[7] 
                    - other.data[4] * other.data[2]  * other.data[11]
                    + other.data[0] * other.data[6]  * other.data[11] ) * invDet;


    data[7]  =  (   other.data[8] * other.data[5] * other.data[3]  
                    - other.data[4] * other.data[9] * other.data[3]  
                    - other.data[8] * other.data[1] * other.data[7] 
                    + other.data[0] * other.data[9] * other.data[7] 
                    + other.data[4] * other.data[1] * other.data[11]
                    - other.data[0] * other.data[5] * other.data[11] ) * invDet;
}

// Sets this matrix to be the rotation matrix corresponding to the given quaternion.
void Matrix4::SetOrientationAndPosition(const Quaternion &quat, const Vector3 &pos)
{
    // Row 1
    data[0] = 1 - (2 * quat.j * quat.j + 2 * quat.k * quat.k);
    data[1] = 2 * quat.i * quat.j + 2 * quat.k * quat.w;
    data[2] = 2 * quat.i * quat.k - 2 * quat.j * quat.w;
    data[3] = pos.x;

    // Row 2
    data[4] = 2 * quat.i * quat.j - 2 * quat.k * quat.w;
    data[5] = 1 - (2 * quat.i * quat.i + 2 * quat.k * quat.k);
    data[6] = 2 * quat.j * quat.k + 2 * quat.i * quat.w;
    data[7] = pos.y;

    // Row 3
    data[8] = 2 * quat.i * quat.k + 2 * quat.j * quat.w;
    data[9] = 2 * quat.j * quat.k - 2 * quat.i * quat.w;
    data[10] = 1 - (2 * quat.i * quat.i + 2 * quat.j * quat.j);
    data[11] = pos.z;
}

// Transform the given vector by this matrix.
Vector3 Matrix4::Transform(const Vector3 &vector) const
{
    return (*this) * vector;
}

// Transform the given direction vector by this matrix.
Vector3 Matrix4::TransformDirection(const Vector3 &vector) const
{
    return Vector3(vector.x * data[0] + vector.y * data[1] * vector.z * data[2], 
                    vector.x * data[4] + vector.y * data[5] * vector.z * data[6],
                    vector.x * data[8] + vector.y * data[9] * vector.z * data[10]);
}

// Transform the given vector by the transormational inverse of this matrix.
Vector3 Matrix4::TransformInverse(const Vector3 &vector) const
{
    Vector3 temp = vector;
    temp.x -= data[3];
    temp.y -= data[7];
    temp.z -= data[11];

    return Vector3(temp.x * data[0] + temp.y * data[4] * temp.z * data[8], 
                    temp.x * data[1] + temp.y * data[5] * temp.z * data[9],
                    temp.x * data[2] + temp.y * data[6] * temp.z * data[10]);
}

// Transform the given direciton vector by the transformational inverse of this matrix.
Vector3 Matrix4::TransformInverseDirection(const Vector3 &vector) const
{
    return Vector3(vector.x * data[0] + vector.y * data[4] * vector.z * data[8], 
                    vector.x * data[1] + vector.y * data[5] * vector.z * data[9],
                    vector.x * data[2] + vector.y * data[6] * vector.z * data[10]);
}
