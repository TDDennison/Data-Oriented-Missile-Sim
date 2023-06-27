#ifndef QUATERNION_H
#define QUATERNION_H

#include <math.h>

#include "Vector3.h"
#include "../Core/TypeDefinitions.h"

// Holds a three-degrees-of-freedom orientation.
class Quaternion
{
    public:
    Quaternion() : w(0.0), i(0.0), j(0.0), k(0.0) {};
    Quaternion(real w_, real i_, real j_, real k_) : w(w_), i(i_), j(j_), k(k_) {}
    ~Quaternion(){};

    union 
    {
        struct
        {
            // Holds the real component of the quaternion.
            real w;

            // Holds the first complex component of the quaternion.
            real i;

            // Holds the second complex component of the quaternion.
            real j;

            // Holds the third complex component of the quaternion.
            real k;
        };

        // Holds the quaternion data in array form.
        real data[4];        
    };

    // Adds the given quaternion to this quaternion.
    void operator+=(const Quaternion &other)
    {
        w += other.w;
        i += other.i;
        j += other.j;
        k += other.k;
    }

    // Multiplies the quaternion by the given quaternion.
    void operator*=(const Quaternion &other)
    {
        Quaternion q = *this;

        w = q.w * other.w - q.i * other.i - q.j * other.j - q.k * other.k;
        i = q.w * other.i + q.i * other.w + q.j * other.k - q.k * other.j;
        j = q.w * other.j - q.i * other.k + q.j * other.w + q.k * other.i;
        k = q.w * other.k + q.i * other.j - q.j * other.i + q.k * other.w;
    }

    // Multiplies the quaternion by the given scalar value.
    void operator*=(const real &scalar)
    {
        w *= scalar;
        i *= scalar;
        j *= scalar;
        k *= scalar;
    }

    // Checks for value equality
    bool operator==(const Quaternion &other)
    {
        return w == other.w && i == other.i && j == other.j && k == other.k;
    }

    // Adds the given vector to this one, scaled by the given amount.
    // This is used to upate the orientation quaternion by a rotation and time.
    //
    // This is the logic to execute the equation:
    //      quat_prime = quat + (dt/2)(q_omega)(quat)
    // where quat is the starting quaternion,
    //       quat_prime is the resultant quaternion,
    //       q_omega is the quaternion form of the angular velocity,
    // and   dt is the time scaling factor.
    void AddScaledVector(const Vector3 &vector, real scale) {
        real halfScale = scale * 0.5;
        Quaternion q{0.0, vector.x * halfScale, vector.y * halfScale, vector.z * halfScale};
        q *= *this;
        *this += q;
        Normalize();
    }

    Quaternion Conjugate()
    {
        return Quaternion{w, -i, -j, -k};
    }
    
    // Normalizes the quaternion to unit length, making it a valid orientation quaternion.
    void Normalize()
    {
        real sqrMag = w*w + i*i + j*j + k*k;

        // Check for zero-length quaternion, and use the no-rotation quaternion in that case.
        if (sqrMag == 0.0) {
            w = 1;
            return;
        }

        // Divide by the magnitude to get the unit length quaternion.
        real d = (real)(1.0 / (sqrt(sqrMag)));
        w *= d;
        i *= d;
        j *= d;
        k *= d;
    }

    void RotateByVector(const Vector3 &vector)
    {
        Quaternion q(0.0, vector.x, vector.y, vector.z);
        (*this) *= q;
    }
};

#endif //QUATERNION_H