#ifndef UTILITIES_H
#define UTILITIES_H

#include "Vector3.h"

class Utilities {
    public:
    // Calculates the distance between two points.
    static real CalculateDistance(Vector3 a, Vector3 b);

    static Vector3 CalculateVectorBetweenPoints(Vector3 a, Vector3 b);

    static Vector3 LLAtoECEF(float lat, float lon, float alt);
    
    //================================================================================
    // Object Geometry
    //================================================================================
    static Vector3 GetObjectGeometry(unsigned short objId);

    static Vector3 GetObjectOffset(unsigned short objId);

};


#endif //UTILITIES_H