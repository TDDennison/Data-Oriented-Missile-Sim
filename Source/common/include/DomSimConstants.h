#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <inttypes.h>
#include <string>

#include "Vector3.h"

namespace DomSim::Constants
{
    inline static const bool     DEFAULT_BOOLEAN = false;
    inline static const uint8_t  DEFAULT_UINT8   = 0;
    inline static const uint16_t DEFAULT_UINT16  = 0;
    inline static const uint32_t DEFAULT_UINT32  = 0;
    inline static const uint64_t DEFAULT_UINT64  = 0;
    inline static const int8_t   DEFAULT_INT8    = 0;
    inline static const int16_t  DEFAULT_INT16   = 0;
    inline static const int32_t  DEFAULT_INT32   = 0;
    inline static const int64_t  DEFAULT_INT64   = 0;
    inline static const float    DEFAULT_FLOAT   = 0.0f;
    inline static const double   DEFAULT_DOUBLE  = 0.0;

    // Valid input set property designators.
    inline static const char *EXECUTION_ORDER_EARTH_SYSTEM = "Earth System Execution Order";
    inline static const char *EXECUTION_ORDER_TEST_SOFTWARE_SYSTEM = "Test Software System Execution Order";
    inline static const char *INTEGRATION_SYSTEM_TYPE = "Integration System Type";
    inline static const char *SIMULATION_MAX_TIME = "Simulation Max Time";
    inline static const char *SIMULATION_TOP_RATE = "Simulation Top Rate";

    // Reserved Input File Attribute Names
    inline static const char *RESERVED_ATTRIBUTE_MISSILE_STARTING_LOCATIONS = "Missile Starting Locations";
    inline static const char *RESERVED_ATTRIBUTE_TARGET_POINTS = "Target Points";

    // Logfile names
    inline static const char *LOG_FILE_FIRST_STAGE_SRM_MANAGER = "FirstStageSrmManager" ;

    // Missile component offsets.
    // These should be moved to configurations when necessary.
    inline static const Vector3 TVC_OFFSET_FROM_ORIGIN = Vector3::Zero();
    inline static const Vector3 FIRST_STAGE_BOOSTER_OFFSET_FROM_ORIGIN = Vector3(5.0, 0.0, 0.0); // 5 units along the x-axis
    inline static const Vector3 SECOND_STAGE_BOOSTER_OFFSET_FROM_ORIGIN = Vector3(15.0, 0.0, 0.0); // 10 units along the x-axis
}

#endif //CONSTANTS_H