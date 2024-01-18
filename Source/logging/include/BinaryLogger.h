#ifndef LOGGING_SYSTEM_H
#define LOGGING_SYSTEM_H

#include <cstring>
#include <string>
#include <fstream>

#include "CoreConstants.h"
#include "Configurations.h"

class BinaryLogger
{
    public:

    BinaryLogger(std::string fileName);

    std::string getFileName();

    void WriteAll();
    
    void WriteToBuffer(void *obj, size_t sizeOfComponent, unsigned int numComponents, float *time);

    private:

    std::string fileName_;
    std::fstream outputFile_;
    uint bufferIndex_ = 0;
    char buffer_[1048576]{0}; // One megabyte buffer size.
};

#endif //LOGGING_SYSTEM_H