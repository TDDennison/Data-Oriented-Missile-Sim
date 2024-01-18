#ifndef SOFTWARE_COMPONENT_H
#define SOFTWARE_COMPONENT_H

#include "Component.h"
#include "TypeDefinitions.h"

// This class should be inherited by any software based component that is
// not intended to run in every frame.
class SoftwareComponent : public Component
{
    public:
    
    // Constructors
    SoftwareComponent();
    SoftwareComponent(uint16_t id);

    // Frequency the software model should be executed at. In units of seconds.
    real executionFrequency;

    // The time the software component was last executed. In units of seconds.
    real lastTimeExecuted = 0.0;
};

#endif //SOFTWARE_COMPONENT_H