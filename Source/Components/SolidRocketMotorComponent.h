#ifndef SOLID_ROCKET_MOTOR_COMPONENT_H
#define SOLID_ROCKET_MOTOR_COMPONENT_H

#include "Component.h"
#include "../Core/TypeDefinitions.h"

struct SolidRocketMotorComponent : public Component
{
    // Constructor
    SolidRocketMotorComponent() : Component(DEFAULT_COMPONENT_ID) {}
    SolidRocketMotorComponent(uint16_t id) : Component(id) {}

    real inertMass;
    real propellantMass;
    real thrust;
};

#endif //SOLID_ROCKET_MOTOR_COMPONENT_H