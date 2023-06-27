#ifndef VECTOR_3_H
#define VECTOR_3_H

#include <math.h>
#include "../Core/TypeDefinitions.h"

// Holds a vector in three dimensions.
class Vector3
{
    public:
    Vector3() : x(0.0), y(0.0), z(0.0) {}
    Vector3(real x, real y, real z) : x(x), y(y), z(z) {}
    ~Vector3(){}

    // ========================================
    // ========== Operator Overloads ==========
    // ========================================

    // Checks if two vectors are equal to each other.
    bool operator==(const Vector3 &other) {
        return (x == other.x) && (y == other.y) && (z == other.z);
    }

    // Adds the given vector to this vector.
    void operator+=(const Vector3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    // Returns the value of the given vector added to this vector.
    Vector3 operator+(const Vector3 &other)
    {
        return Vector3(x+other.x, y+other.y, z+other.z);
    }

    // Subtracts the given vector from this vector.
    void operator-=(const Vector3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    // Returns the value of the given vector subtracted from this vector.
    Vector3 operator-(const Vector3 &other)
    {
        return Vector3(x-other.x, y-other.y, z-other.z);
    }

    // Multiplies this vector by the given scalar value.
    void operator*=(const real value)
    {
        x*= value;
        y*= value;
        z*= value;
    }

    // Calculates and returns the scalar product of this vector with the
    // given vector.
    real operator*(const Vector3 &other) const
    {
        return x*other.x + y*other.y + z*other.z;
    }

    // Returns a copy of this vector scaled by the given value.
    Vector3 operator*(const real value) const
    {
        return Vector3(x*value, y*value, z*value);
    }

    // Updates this vector to be the vector product of its current
    // value and the given vector.
    void operator%=(const Vector3 &other)
    {
        *this = VectorProduct(other);
    }

    // Calculates and returns the vector product of this vector with the given vector.
    Vector3 operator%(const Vector3 &other) const
    {
        return Vector3(y*other.z - z*other.y,
                        z*other.x - x*other.z,
                        x*other.y - y*other.x);
    }

    // ========================================
    // ========== Static Methods ==============
    // ========================================
    static void MakeOrthonormalBasis(Vector3 &a, Vector3 &b, Vector3 &c)
    {
        a.Normalize(); 
        c = a % b;

        // If c has zero magnitude, a and b are parallel.
        if (c.SquareMagnitude() == 0.0) return; // Or generate an error.

        c.Normalize();
        b = c % a;
    }

    static Vector3 Zero() { return Vector3{0.0, 0.0, 0.0}; }

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
    void AddScaledVector(const Vector3& vector, real scale)
    {
        *this += vector * scale;
    }

    // Calculates and returns a component-wise product of this vector
    // with the given vector.
    Vector3 ComponentProduct(const Vector3 &other) const
    {
        return Vector3(x*other.x, y*other.y, z*other.z);
    }

    // Performs a component-wise product with the given vector and sets
    // this vector to its result.
    void ComponentProductUpdate(const Vector3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }

    // Gets the magnitude of this vector.
    real Magnitude() const
    {
        return sqrt(x*x + y*y + z*z);
    }

    // Turns a non-zero vector inot a vector of unit length.
    void Normalize()
    {
        real mag = Magnitude();
        if (mag > 0.0)
        {
            (*this) *= 1/mag;
        }
    }

    // Calculates and returns the scalar product of this vector with the given vector.
    real ScalarProduct(const Vector3 &other) const
    {
        return x * other.x +
               y * other.y +
               z * other.z;
    }

    // Gets the squared magnitude of this vector
    real SquareMagnitude() const
    {
        return x*x + y*y + z*z;
    }

    // Calculates and returns the vector product of this vector with the given vector.
    Vector3 VectorProduct(const Vector3 &other) const
    {
        return Vector3(y*other.z - z*other.y,
                        z*other.x - x*other.z,
                        x*other.y - y*other.x);
    }
};

#endif //VECTOR_3_H