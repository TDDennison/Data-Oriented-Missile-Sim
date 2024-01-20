#ifndef CORE_CONSTANTS_H
#define CORE_CONSTANTS_H

#include <stdint.h>

namespace Core::Constants {

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

    inline static const char *LOG_FILE_EXTENSION_BINARY = ".bin";
    inline static const char *LOG_FILE_EXTENSION_CSV = ".csv";
    inline static const char *LOG_FILE_EXTENSION_TXT = ".txt";

}

#endif //CORE_CONSTANTS_H