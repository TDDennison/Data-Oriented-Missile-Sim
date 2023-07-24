#ifndef CLOCK_COMPONENT_H
#define CLOCK_COMPONENT_H

#include "Component.h"
#include "../Core/TypeDefinitions.h"

struct ClockComponent : public Component
{
    // Constructors
    ClockComponent() : Component(DEFAULT_COMPONENT_ID) {}
    ClockComponent(uint16_t id) : Component(id) {}

    // The current time of the clock component. In units of seconds.
    real time;
};

#endif //CLOCK_COMPONENT_H