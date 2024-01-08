#ifndef COMPONENT_UTILITIES_H
#define COMPONENT_UTILITIES_H

#include "Component.h"
#include <map>
#include <string>
#include <sstream>

namespace ComponentUtilities
{
    // Maximum number of submasses based on analysis of the system.
    // Currently just a guess, analyze the system to find the real 
    // number in the future.
    static inline const uint8_t MAX_SUB_MASSES = 10;

    enum ComponentDesignators : uint8_t
    {
        NONE = 0,
        ACCUMULATOR,
        AGGREGATE,
        CLOCK,
        FIRST_STAGE_SRM,
        SECOND_STAGE_SRM,
        TEST_SOFTWARE,
    };

    static inline const std::string COMPONENT_DESIGNATOR_NONE = "None";
    static inline const std::string COMPONENT_DESIGNATOR_ACCUMULATOR = "Accumulator";
    static inline const std::string COMPONENT_DESIGNATOR_AGGREGATE = "Aggregate";
    static inline const std::string COMPONENT_DESIGNATOR_CLOCK = "Clock";
    static inline const std::string COMPONENT_DESIGNATOR_FIRST_STAGE_SRM = "First Stage SRM";
    static inline const std::string COMPONENT_DESIGNATOR_SECOND_STAGE_SRM = "Second Stage SRM";
    static inline const std::string COMPONENT_DESIGNATOR_TEST_SOFTWARE = "Test Software";

    static const std::map<ComponentDesignators, std::string> DesignatorsToStrings {
        {ComponentDesignators::NONE,             COMPONENT_DESIGNATOR_NONE},
        {ComponentDesignators::ACCUMULATOR,      COMPONENT_DESIGNATOR_ACCUMULATOR},
        {ComponentDesignators::AGGREGATE,        COMPONENT_DESIGNATOR_AGGREGATE},
        {ComponentDesignators::CLOCK,            COMPONENT_DESIGNATOR_CLOCK},
        {ComponentDesignators::FIRST_STAGE_SRM,  COMPONENT_DESIGNATOR_FIRST_STAGE_SRM},
        {ComponentDesignators::SECOND_STAGE_SRM, COMPONENT_DESIGNATOR_SECOND_STAGE_SRM},
        {ComponentDesignators::TEST_SOFTWARE,    COMPONENT_DESIGNATOR_TEST_SOFTWARE},
    };

    inline unsigned short CreateComponentId(unsigned int missileId, unsigned short compDesignator)
    {
        return (missileId << 8) | compDesignator;
    }

    inline std::string DecomposeComponentId(unsigned short componentId)
    {
        std::stringstream stream;
        unsigned short missileId = (componentId >> 8) & 0xFF;

        //std::map<ComponentDesignators, std::string>::iterator itr = 
        std::string componentName = DesignatorsToStrings.at(static_cast<ComponentDesignators>(componentId & 0xFF));
        stream << "Missile: " << missileId << "\t";
        stream << "Component Type: " << componentName;

        return stream.str();
    }
}

#endif // COMPONENT_UTILITIES_H