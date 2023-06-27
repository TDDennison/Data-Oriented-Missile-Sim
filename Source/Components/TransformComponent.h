#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"
#include "../MathTypes/Vector3.h"
#include "../MathTypes/Quaternion.h"
#include "../MathTypes/Matrix4.h"

struct TransformComponent : public Component
{
    // The position of the origin of the missile station frame in ECI.
    Vector3 position_eci; 

    // The angular orientation of the entity in ECI.
    Quaternion orientation_eci; 

    // Holds a transform matrix for converting body space into world space and vice versa.
    Matrix4 transformMatrix;
};

#endif //TRANSFORM_COMPONENT_H