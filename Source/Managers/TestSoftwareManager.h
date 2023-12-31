#ifndef TEST_SOFTWARE_MANAGER_H
#define TEST_SOFTWARE_MANAGER_H

#include "ComponentManager.h"
#include "../Components/MassComponent.h"
#include "Managers.h"

class TestSoftwareManager : public ComponentManager<SoftwareComponent, MaxComponents>
{
    public:

    TestSoftwareManager() : ComponentManager("TestSoftwareManager") {}
};

#endif // TEST_SOFTWARE_MANAGER_H