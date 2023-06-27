#ifndef COMPONENT_UTILITIES_H
#define COMPONENT_UTILITIES_H

#include "Component.h"

namespace ComponentUtilities
{
    enum ComponentDesignators
    {
        ACCUMULATOR = 0,
        AGGREGATE,
        FIRST_STAGE_SRM,
        SECOND_STAGE_SRM,
    };

    inline unsigned short CreateComponentId(unsigned int missileId, unsigned short compDesignator)
    {
        return (missileId << 8) | compDesignator;
    }

    inline void SetComponentId(Component& component, unsigned int missileId, unsigned short compDesignator)
    {
        component.componentId = CreateComponentId(missileId, compDesignator);
    }
}

#endif // COMPONENT_UTILITIES_H