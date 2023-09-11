#ifndef SOLID_ROCKET_MOTOR_COMPONENT_H
#define SOLID_ROCKET_MOTOR_COMPONENT_H

#include "Component.h"
#include "../Core/TypeDefinitions.h"

// NOTE: THIS STRUCT WILL MOST LIKELY GO AWAY ONCE A LOOKUP TABLE IS USED TO DETERMINE THRUST
//       AT THAT TIME THE MASSES CAN BE AGGREGATED INTO A MASS COMPONENT

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