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

    static Vector3 LLAtoECEF(float lat, float lon, float alt)
    {
        // TODO: FIGURE OUT HOW TO ALLOW FOR NON_SPHERICAL EARTH SHAPE
        // ALSO I DON'T THINK THIS MATH IS CORRECT

        const float EARTH_RADIUS_METERS = 6371000.0;

        //N = ell.semimajor_axis ** 2 / sqrt(ell.semimajor_axis ** 2 * cos(lat) ** 2 + ell.semiminor_axis ** 2 * sin(lat) ** 2);
        float N = EARTH_RADIUS_METERS;

        // Change degrees to radians
        lat *= M_PI / 180;
        lon *= M_PI / 180;

        // Compute cartesian (geocentric) coordinates given  (curvilinear) geodetic
        // coordinates.
        float x = (N + alt) * cos(lat) * cos(lon);
        float y = (N + alt) * cos(lat) * sin(lon);
        float z = (N + alt) * sin(lat);

        return Vector3{x, y, z};
    }
}

#endif //HELPER_METHODS_H