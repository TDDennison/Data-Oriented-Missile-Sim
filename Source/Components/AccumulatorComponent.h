#ifndef ACCUMULATOR_COMPONENT_H
#define ACCUMULATOR_COMPONENT_H

#include "Component.h"
#include "../MathTypes/Vector3.h"

struct AccumulatorComponent : public Component
{
    // Constructors
    AccumulatorComponent() : Component(DEFAULT_COMPONENT_ID) {}
    AccumulatorComponent(uint16_t id) : Component(id) {}

    // Holds the accumulated forces for an entity in a frame defined in the ECI frame.
    Vector3 forceAccumulator_eci;

    // Holds the accumulated torques for an entity in a frame defined in the ECI frame.
    Vector3 torqueAccumulator_eci;
};

#endif //ACCUMULATOR_COMPONENT_H