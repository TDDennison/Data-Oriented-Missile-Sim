#ifndef INTEGRATION_SYSTEM
#define INTEGRATION_SYSTEM

#include "System.h"

class IntegrationSystem : public System
{
    public:
    virtual void Update(float dt, float &dtOut, bool &shouldLog) = 0;

    protected:
    bool shouldLog_ = false;
};

#endif // INTEGRATION_SYSTEM