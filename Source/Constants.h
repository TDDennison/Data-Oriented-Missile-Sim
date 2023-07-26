#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <inttypes.h>

class Constants
{
    public:
    inline static const bool DEFAULT_BOOLEAN = false;
    inline static const uint8_t DEFAULT_UINT8 = 0;
    inline static const uint16_t DEFAULT_UINT16 = 0;
    inline static const uint32_t DEFAULT_UINT32 = 0;
    inline static const uint64_t DEFAULT_UINT64 = 0;
    inline static const int8_t  DEFAULT_INT8 = 0;
    inline static const int16_t DEFAULT_INT16 = 0;
    inline static const int32_t DEFAULT_INT32 = 0;
    inline static const int64_t DEFAULT_INT64 = 0;
    inline static const float DEFAULT_FLOAT = 0.0f;
    inline static const double DEFAULT_DOUBLE = 0.0;

    // Valid input set property designators.
    inline static const char *EXECUTION_ORDER_EARTH_SYSTEM = "Earth System Execution Order";
    inline static const char *EXECUTION_ORDER_TEST_SOFTWARE_SYSTEM = "Test Software System Execution Order";
    inline static const char *INTEGRATION_SYSTEM_TYPE = "Integration System Type";
    inline static const char *RESERVED_ATTRIBUTE_MISSILE_STARTING_LOCATIONS = "Missile Starting Locations";
    inline static const char *SIMULATION_MAX_TIME = "Simulation Max Time";
    inline static const char *SIMULATION_TOP_RATE = "Simulation Top Rate";
};

#endif //CONSTANTS_H