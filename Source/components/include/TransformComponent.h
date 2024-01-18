#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"

class TransformComponent : public Component
{
    public:

    // Constructors
    TransformComponent();
    TransformComponent(TransformComponent& other);
    TransformComponent(uint16_t id);

    // The position of the origin of the missile station frame in ECI.
    Vector3 position_eci{}; 

    // The angular orientation of the entity in ECI.
    Quaternion orientation_eci{}; 

    // Holds a transform matrix for converting body space into world space and vice versa.
    Matrix4 transformMatrix{};
};

#endif //TRANSFORM_COMPONENT_H