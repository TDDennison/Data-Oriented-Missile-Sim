#ifndef SOFTWARE_COMPONENT_H
#define SOFTWARE_COMPONENT_H

#include "Component.h"
#include "../Core/TypeDefinitions.h"

// This struct should be inherited by any software based component that is
// not intended to run in every frame.
struct SoftwareComponent : public Component
{
    // Frequency the software model should be executed at. In units of seconds.
    real executionFrequency;

    // The time the software component was last executed. In units of seconds.
    real lastTimeExecuted;
};

#endif //SOFTWARE_COMPONENT_H