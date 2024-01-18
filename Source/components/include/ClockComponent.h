#ifndef CLOCK_COMPONENT_H
#define CLOCK_COMPONENT_H

#include "Component.h"
#include "TypeDefinitions.h"

class ClockComponent : public Component
{
    public:

    // Constructors
    ClockComponent();
    ClockComponent(uint16_t id);

    // The current time of the clock component. In units of seconds.
    real time;
};

#endif //CLOCK_COMPONENT_H