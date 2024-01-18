#ifndef CORE_ENUMERATIONS_H
#define CORE_ENUMERATIONS_H

#include <stdint.h>

namespace Core::Enumerations {
    enum AttributeType { BOOLEAN, 
                        UINT8, 
                        UINT16, 
                        UINT32,
                        UINT64,
                        INT8, 
                        INT16, 
                        INT32, 
                        INT64,
                        FLOAT, 
                        DOUBLE};

    // Enumeration to hold the type designators for the intergration system.
    enum IntegrationSystemType : uint32_t
    {
        EULER = 1,
        RUNGE_KUTTA_2,
        RUNGE_KUTTA_4,
    };

    // Enumeration to hold the type designators for output file types.
    enum PostProcessLogType 
    {
        CSV = 1,
        TEXT
    };

}

#endif //CORE_ENUMERATIONS_H