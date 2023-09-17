#ifndef TEST_SOFTWARE_SYSTEM_H
#define TEST_SOFTWARE_SYSTEM_H

#include "System.h"

#include "../Managers/ClockManager.h"
#include "../Managers/Managers.h"

class TestSoftwareSystem : public System
{
    public:

    TestSoftwareSystem(ClockManager* clockManager, TestSoftwareManager* tswManager) : clockManager_(clockManager), testSoftwareManager_(tswManager) { }

    void Initialize() override {
        // Grab the necessary attribtues.
        AttributesManager *attributesManager = AttributesManager::GetInstance();

        executionOrder_ = attributesManager->GetAttribute<uint16_t>(Constants::EXECUTION_ORDER_TEST_SOFTWARE_SYSTEM);

        std::cout << "Test Software System execution order is: " << executionOrder_ << std::endl;
    }

    void Update(float dt) override {
        for (auto & entity : registeredEntities) {
            SoftwareComponent& softwareComponent = testSoftwareManager_->Lookup(entity);
            ClockComponent& clockComponent = clockManager_->Lookup(entity);

            // std::cout << "Current missile clock time: " << clockComponent.time << std::endl;
            // std::cout << "Software component last time executed: " << softwareComponent.lastTimeExecuted << std::endl;
            // std::cout << "Software component execution frequency: " << softwareComponent.executionFrequency << std::endl;

            //Check if the software entity should run.
            if ((float)clockComponent.time == (float)(softwareComponent.lastTimeExecuted + softwareComponent.executionFrequency))
            {
                //std::cout << "Software component executing at time: " << clockComponent.time << std::endl;
                softwareComponent.lastTimeExecuted = clockComponent.time;
            }
        }
    }

    void AddSoftwareComponent(Entity& entity, SoftwareComponent& softwareComponent)
    {
        testSoftwareManager_->Add(entity, softwareComponent);
    }

    private:

    // Private class used to register attributes prior to runtime starting.
    // This is done through the use of static construction of this class.
    class Attributes
    {
        public:
        Attributes()
        {
            std::cout << "Test Software System adding attributes." << std::endl;
            AttributesManager *attributesManager = AttributesManager::GetInstance();

            attributesManager->AddAttribute<uint16_t>(Constants::EXECUTION_ORDER_TEST_SOFTWARE_SYSTEM, AttributeType::UINT16, Constants::DEFAULT_UINT16);
        }
    };

    inline static const Attributes attributes{}; // Static constructor used to register attributes before main() is started.

    ClockManager* clockManager_;
    TestSoftwareManager* testSoftwareManager_;  
};

#endif //TEST_SOFTWARE_SYSTEM_H