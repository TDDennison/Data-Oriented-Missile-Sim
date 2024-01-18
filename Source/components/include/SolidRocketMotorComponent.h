#ifndef SOLID_ROCKET_MOTOR_COMPONENT_H
#define SOLID_ROCKET_MOTOR_COMPONENT_H

#include "Component.h"
#include "TypeDefinitions.h"

// NOTE: THIS CLASS WILL MOST LIKELY GO AWAY ONCE A LOOKUP TABLE IS USED TO DETERMINE THRUST
//       AT THAT TIME THE MASSES CAN BE AGGREGATED INTO A MASS COMPONENT

class SolidRocketMotorComponent : public Component
{
    public:
    // Constructor
    SolidRocketMotorComponent();
    SolidRocketMotorComponent(uint16_t id);

    real inertMass;
    real propellantMass;
    real thrust;
};

#endif //SOLID_ROCKET_MOTOR_COMPONENT_H