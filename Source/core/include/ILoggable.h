#ifndef ILOGGABLE_H
#define ILOGGABLE_H

#include "CoreEnumerations.h"
#include "Utilities.h"

class ILoggable
{
    public:
    virtual void WriteToLog(float *time) = 0;
    virtual void FinalizeLog() = 0;
    virtual bool PostProcessLog(Core::Enumerations::PostProcessLogType outputType) = 0;
    virtual bool ParseBinaryToText(std::string fileName) = 0;
};

#endif // ILOGGABLE_H