#ifndef SOLID_ROCKET_MOTOR_COMPONENT_H
#define SOLID_ROCKET_MOTOR_COMPONENT_H

#include "Component.h"
#include "../Core/TypeDefinitions.h"

struct SolidRocketMotorComponent : public Component
{
    real inertMass;
    real propellantMass;
    real thrust;
};

#endif //SOLID_ROCKET_MOTOR_COMPONENT_H