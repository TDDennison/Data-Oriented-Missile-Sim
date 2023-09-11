#ifndef ILOGGABLE_H
#define ILOGGABLE_H

class ILoggable
{
    public:
    virtual void WriteToLog(float time) = 0;
    virtual void FinalizeLog(float time) = 0;
};

#endif // ILOGGABLE_H