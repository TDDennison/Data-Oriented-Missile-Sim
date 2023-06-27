#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "Component.h"
#include "../MathTypes/Vector3.h"

struct MovementComponent : public Component
{
    Vector3 velocity_eci;             // The linear velocity of the entity in ECI.
    Vector3 acceleration_eci;         // The linear acceleration of the entity in ECI.
    Vector3 angular_velocity_eci;     // The angular velocity of the entity in ECI.
    Vector3 angular_acceleration_eci; // The angular acceleration of the entity in ECI.
};

#endif //MOVEMENT_COMPONENT_H