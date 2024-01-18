#ifndef VECTOR_3_H
#define VECTOR_3_H

#include <math.h>
#include "TypeDefinitions.h"

// Holds a vector in three dimensions.
class Vector3
{
    public:
    Vector3();
    Vector3(real x, real y, real z);
    ~Vector3();

    // ========================================
    // ========== Operator Overloads ==========
    // ========================================

    // Checks if two vectors are equal to each other.
    bool operator==(const Vector3 &other);

    // Adds the given vector to this vector.
    void operator+=(const Vector3 &other);

    // Returns the value of the given vector added to this vector.
    Vector3 operator+(const Vector3 &other);

    // Subtracts the given vector from this vector.
    void operator-=(const Vector3 &other);

    // Returns the value of the given vector subtracted from this vector.
    Vector3 operator-(const Vector3 &other);

    // Multiplies this vector by the given scalar value.
    void operator*=(const real value);

    // Calculates and returns the scalar product of this vector with the
    // given vector.
    real operator*(const Vector3 &other) const;

    // Returns a copy of this vector scaled by the given value.
    Vector3 operator*(const real value) const;

    // Updates this vector to be the vector product of its current
    // value and the given vector.
    void operator%=(const Vector3 &other);

    // Calculates and returns the vector product of this vector with the given vector.
    Vector3 operator%(const Vector3 &other) const;

    // ========================================
    // ========== Static Methods ==============
    // ========================================
    static void MakeOrthonormalBasis(Vector3 &a, Vector3 &b, Vector3 &c);

    static Vector3 Zero();

    // ========================================
    // ========== Accessors ===================
    // ========================================

    // Holds the value along the x-axis.
    real x;

    // Holds the value along the y-axis.
    real y;

    // Holds the value along the z-axis.
    real z;

    // ========================================
    // ========== Public Methods ==============
    // ========================================

    // Adds the given vector to this, scaled by the given amount.
    void AddScaledVector(const Vector3& vector, real scale);

    // Calculates and returns a component-wise product of this vector
    // with the given vector.
    Vector3 ComponentProduct(const Vector3 &other) const;

    // Performs a component-wise product with the given vector and sets
    // this vector to its result.
    void ComponentProductUpdate(const Vector3 &other);

    // Gets the magnitude of this vector.
    real Magnitude() const;

    // Turns a non-zero vector into a vector of unit length.
    void Normalize();

    // Calculates and returns the scalar product of this vector with the given vector.
    real ScalarProduct(const Vector3 &other) const;

    // Gets the squared magnitude of this vector
    real SquareMagnitude() const;

    // Calculates and returns the vector product of this vector with the given vector.
    Vector3 VectorProduct(const Vector3 &other) const;
};

#endif //VECTOR_3_H