#ifndef INTEGRATION_SYSTEM
#define INTEGRATION_SYSTEM

#include "System.h"

class IIntegrationSystem : public System
{
    public:
    virtual void Update(float dt, float &dtOut, bool &shouldLog, bool &allowMassDecrement) = 0;
};

#endif // INTEGRATION_SYSTEM