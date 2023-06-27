#ifndef HELPER_METHODS_H
#define HELPER_METHODS_H

#include <cmath>
#include "Core/TypeDefinitions.h"
#include "MathTypes/Vector3.h"

namespace HelperMethods
{
    // Calculates the distance between two points.
    static real CalculateDistance(Vector3 a, Vector3 b)
    {
        Vector3 diff = a - b;

        real distance = diff.Magnitude();
        return distance;
    }
}

#endif //HELPER_METHODS_H