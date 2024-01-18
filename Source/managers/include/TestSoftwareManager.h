#ifndef TEST_SOFTWARE_MANAGER_H
#define TEST_SOFTWARE_MANAGER_H

#include "ComponentManager.h"
#include "SoftwareComponent.h"
#include "ManagersConstants.h"

class TestSoftwareManager : public ComponentManager<SoftwareComponent, Managers::Constants::MaxComponents>
{
    public:

    TestSoftwareManager();
};

#endif // TEST_SOFTWARE_MANAGER_H