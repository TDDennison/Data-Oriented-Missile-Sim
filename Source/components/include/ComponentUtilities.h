#ifndef COMPONENT_UTILITIES_H
#define COMPONENT_UTILITIES_H

// STL Includes
#include <map>
#include <stdint.h>
#include <sstream>
#include <string>

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

    unsigned short CreateComponentId(unsigned int missileId, unsigned short compDesignator);

    std::string DecomposeComponentId(unsigned short componentId);
}


#endif //OMPONENT_UTILITIES_H