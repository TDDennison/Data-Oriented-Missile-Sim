#include "AttributesManager.h"
#include "CoreEnumerations.h"
#include "TestSoftwareSystem.h"

TestSoftwareSystem::TestSoftwareSystem(ClockManager* clockManager, TestSoftwareManager* tswManager) : clockManager_(clockManager), testSoftwareManager_(tswManager) { }


void TestSoftwareSystem::Initialize() {
    // Grab the necessary attribtues.
    AttributesManager *attributesManager = AttributesManager::GetInstance();

    executionOrder_ = attributesManager->GetAttribute<uint16_t>(DomSim::Constants::EXECUTION_ORDER_TEST_SOFTWARE_SYSTEM);

    std::cout << "Test Software System execution order is: " << executionOrder_ << std::endl;
}


void TestSoftwareSystem::Update(float dt, bool &allowMassDecrement) {
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


void TestSoftwareSystem::AddSoftwareComponent(SoftwareComponent& softwareComponent)
{
    testSoftwareManager_->Add(softwareComponent);
}


TestSoftwareSystem::Attributes::Attributes() {
    std::cout << "Test Software System adding attributes." << std::endl;
    AttributesManager *attributesManager = AttributesManager::GetInstance();

    attributesManager->AddAttribute<uint16_t>(DomSim::Constants::EXECUTION_ORDER_TEST_SOFTWARE_SYSTEM, Core::Enumerations::AttributeType::UINT16, Core::Constants::DEFAULT_UINT16);
}
