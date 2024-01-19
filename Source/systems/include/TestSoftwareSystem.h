#ifndef TEST_SOFTWARE_SYSTEM_H
#define TEST_SOFTWARE_SYSTEM_H

#include "System.h"

#include "ClockManager.h"
#include "DomSimConstants.h"
#include "ManagersConstants.h"
#include "SoftwareComponent.h"
#include "TestSoftwareManager.h"

class TestSoftwareSystem : public System
{
    public:

    TestSoftwareSystem(ClockManager* clockManager, TestSoftwareManager* tswManager);

    void Initialize() override;

    void Update(float dt, bool &allowMassDecrement) override;

    void AddSoftwareComponent(SoftwareComponent& softwareComponent);

    private:

    // Private class used to register attributes prior to runtime starting.
    // This is done through the use of static construction of this class.
    class Attributes
    {
        public:
        Attributes();
    };

    inline static const Attributes attributes{}; // Static constructor used to register attributes before main() is started.

    ClockManager* clockManager_;
    TestSoftwareManager* testSoftwareManager_;  
};

#endif //TEST_SOFTWARE_SYSTEM_H