#ifndef TEST_SOFTWARE_SYSTEM_H
#define TEST_SOFTWARE_SYSTEM_H

#include "System.h"

#include "../Managers/ClockManager.h"
#include "../Managers/Managers.h"

class TestSoftwareSystem : public System
{
    public:

    TestSoftwareSystem(ClockManager* clockManager, TestSoftwareManager* tswManager) : clockManager_(clockManager), testSoftwareManager_(tswManager) { }

    void Update(real dt) override {
        for (auto & entity : registeredEntities) {
            SoftwareComponent& softwareComponent = testSoftwareManager_->Lookup(entity);
            ClockComponent& clockComponent = clockManager_->Lookup(entity);

            // std::cout << "Current missile clock time: " << clockComponent.time << std::endl;
            // std::cout << "Software component last time executed: " << softwareComponent.lastTimeExecuted << std::endl;
            // std::cout << "Software component execution frequency: " << softwareComponent.executionFrequency << std::endl;

            //Check if the software entity should run.
            if (clockComponent.time >= softwareComponent.lastTimeExecuted + softwareComponent.executionFrequency)
            {
                std::cout << "Software component executing at time: " << clockComponent.time << std::endl;
                softwareComponent.lastTimeExecuted = clockComponent.time;
            }
        }
    }

    void AddSoftwareComponent(Entity& entity, SoftwareComponent& softwareComponent)
    {
        testSoftwareManager_->Add(entity, softwareComponent);
    }

    private:

    ClockManager* clockManager_;
    TestSoftwareManager* testSoftwareManager_;  
};

#endif //TEST_SOFTWARE_SYSTEM_H