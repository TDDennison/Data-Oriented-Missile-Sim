#include <stdint.h>
#include <cmath>

#include "ComponentUtilities.h"
#include "DomSimConstants.h"
#include "Utilities.h"


// Calculates the distance between two points.
real Utilities::CalculateDistance(Vector3 a, Vector3 b)
{
    Vector3 diff = a - b;

    real distance = diff.Magnitude();
    return distance;
}

Vector3 Utilities::CalculateVectorBetweenPoints(Vector3 a, Vector3 b)
{
    Vector3 diff = b - a;
    return diff;
}

Vector3 Utilities::LLAtoECEF(float lat, float lon, float alt)
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

Vector3 Utilities::GetObjectGeometry(unsigned short objId)
{

    // NOTE: MOVE THESE GEOMETRIES TO THE INPUT FILES WHEN POSSIBLE

    uint8_t componentIdRaw = (objId & 0x0F);
    ComponentUtilities::ComponentDesignators componentId = static_cast<ComponentUtilities::ComponentDesignators>(componentIdRaw);

    switch(componentId)
    {
        case ComponentUtilities::ComponentDesignators::FIRST_STAGE_SRM:
        {
            // Length, width, height in the object frame, with the object frame's axes aligning with the missile frames axes.
            // This is an overall summation.

            // If a 3D rectangle's smallest face is located on plane and centered at the origin of a reference frame with:
            // a length of 10 units in only the positive x-axis
            // a length of 1 unit in both the positive and negative directions along the y-axis
            // a length of 1 unit in both the positive and negative directions along the z-axis
            // The end result of summing the dimensions in each axis would be <10, 0, 0>
            Vector3 lwh{10, 0, 0};
            return lwh;
            break;
        }
        case ComponentUtilities::ComponentDesignators::SECOND_STAGE_SRM:
        {
            // Length, width, height in the object frame, with the object frame's axes aligning with the missile frames axes.
            Vector3 lwh{5, 0, 0};
            return lwh;
            break;
        }
        default:
        {
            return Vector3::Zero();
            break;
        }
    }
}

Vector3 Utilities::GetObjectOffset(unsigned short objId)
{
    // NOTE: MOVE THESE OFFSETS TO THE INPUT FILES WHEN POSSIBLE

    uint8_t componentIdRaw = (objId & 0x0F);
    ComponentUtilities::ComponentDesignators componentId = static_cast<ComponentUtilities::ComponentDesignators>(componentIdRaw);

    switch(componentId)
    {
        case ComponentUtilities::ComponentDesignators::FIRST_STAGE_SRM:
        {
            return DomSim::Constants::FIRST_STAGE_BOOSTER_OFFSET_FROM_ORIGIN;
            break;
        }
        case ComponentUtilities::ComponentDesignators::SECOND_STAGE_SRM:
        {
            return DomSim::Constants::SECOND_STAGE_BOOSTER_OFFSET_FROM_ORIGIN;
            break;
        }
        default:
        {
            return Vector3::Zero();
            break;
        }
    }
}
