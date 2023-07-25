#ifndef COMPONENT_UTILITIES_H
#define COMPONENT_UTILITIES_H

#include "Component.h"

namespace ComponentUtilities
{
    enum ComponentDesignators
    {
        NONE = 0,
        ACCUMULATOR,
        AGGREGATE,
        CLOCK,
        FIRST_STAGE_SRM,
        SECOND_STAGE_SRM,
        TEST_SOFTWARE,
    };

    inline unsigned short CreateComponentId(unsigned int missileId, unsigned short compDesignator)
    {
        return (missileId << 8) | compDesignator;
    }
}

#endif // COMPONENT_UTILITIES_H