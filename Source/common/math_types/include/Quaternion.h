#ifndef QUATERNION_H
#define QUATERNION_H

#include <math.h>

#include "Vector3.h"
#include "TypeDefinitions.h"

// Holds a three-degrees-of-freedom orientation.
class Quaternion
{
    public:
    Quaternion();
    Quaternion(real w_, real i_, real j_, real k_);
    ~Quaternion();

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
    void operator+=(const Quaternion &other);

    // Multiplies the quaternion by the given quaternion.
    void operator*=(const Quaternion &other);

    // Multiplies the quaternion by the given scalar value.
    void operator*=(const real &scalar);

    // Checks for value equality
    bool operator==(const Quaternion &other);

    // Adds the given vector to this one, scaled by the given amount.
    // This is used to upate the orientation quaternion by a rotation and time.
    //
    // This is the logic to execute the equation:
    //      quat_prime = quat + (dt/2)(q_omega)(quat)
    // where quat is the starting quaternion,
    //       quat_prime is the resultant quaternion,
    //       q_omega is the quaternion form of the angular velocity,
    // and   dt is the time scaling factor.
    void AddScaledVector(const Vector3 &vector, real scale);

    Quaternion Conjugate();
    
    // Normalizes the quaternion to unit length, making it a valid orientation quaternion.
    void Normalize();

    void RotateByVector(const Vector3 &vector);
};

#endif //QUATERNION_H