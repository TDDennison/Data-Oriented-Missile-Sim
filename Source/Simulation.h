#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "Entity.h"
#include "Components/SolidRocketMotorComponent.h"
#include "Managers/ClockManager.h"
#include "Managers/EntityManager.h"
#include "Managers/MassManager.h"
#include "Managers/MovementManager.h"
#include "Managers/TransformManager.h"
#include "Systems/BoosterSystem.h"
#include "Systems/EarthSystem.h"
#include "Systems/IntegrationSystem_Euler.h"
#include "Systems/LoggingSystem.h"
#include "Systems/TestSoftwareSystem.h"

class BoosterSystem;

// This class manages the communication between systems.
class Simulation
{
    typedef std::vector<System*> SystemCollection;

    public:
    Simulation();
    ~Simulation();

    void Initialize();
    void InitializeLoggingSystem();

    void RegisterComponent_AccumulatorManager(Entity, AccumulatorComponent&);
    void RegisterComponent_ClockManager(Entity, ClockComponent&);
    void RegisterComponent_MassManager(Entity, MassComponent&);
    void RegisterComponent_MovementManager(Entity, MovementComponent&);
    void RegisterComponent_TransformManager(Entity, TransformComponent&);

    void RegisterEntity_EarthSystem(Entity);
    void RegisterEntity_FirstStageBoosterSystem(Entity, SolidRocketMotorComponent&);
    void RegisterEntity_IntegrationSystem(Entity);
    void RegisterEntity_SecondStageBoosterSystem(Entity, SolidRocketMotorComponent&);
    void RegisterEntity_TestSoftwareSystem(Entity, SoftwareComponent&);

    void RegisterSystem_Booster(BoosterType);
    void RegisterSystem_Earth();
    void RegisterSystem_Integration();
    void RegisterSystem_TestSoftwareSystem();

    void Update();

    private:

    // Private class used to register attributes prior to runtime starting.
    // This is done through the use of static construction of this class.
    class Attributes
    {
        public:
        Attributes()
        {
            std::cout << "Configurations adding attributes." << std::endl;
            AttributesManager *attributesManager = AttributesManager::GetInstance();

            attributesManager->AddAttribute<uint32_t>(Constants::INTEGRATION_SYSTEM_TYPE, AttributeType::UINT32, Constants::DEFAULT_UINT8);
            attributesManager->AddAttribute<int>(Constants::SIMULATION_MAX_TIME, AttributeType::INT32, Constants::DEFAULT_INT32);
            attributesManager->AddAttribute<double>(Constants::SIMULATION_TOP_RATE, AttributeType::DOUBLE, Constants::DEFAULT_DOUBLE);
        }
    };

    inline static const Attributes attributes_{}; // Static constructor used to register attributes before main() is started.
    
    // The maximum amount of time the simulation will run for before ending.
    // Set this property using the input file attributes.
    int maxTime_ = 0;

    // The frequency that the simulation runs at.
    // Set this property using the input file attributes.
    double rate_ = 0.0;

    // Collection of system pointers used to enforce order of execution.
    SystemCollection systems{};

    AccumulatorManager* accumulatorManager_;
    ClockManager* clockManager_;
    MassManager* massManager_;
    MovementManager* movementManager_;
    TestSoftwareManager* testSoftwareManager_;
    TransformManager* transformManager_;
    BoosterSystem* firstStageBoosterSystem_;
    BoosterSystem* secondStageBoosterSystem_;
    EarthSystem* earthSystem_;
    System* integrationSystem_;
    LoggingSystem* loggingSystem_;
    TestSoftwareSystem* testSoftwareSystem_;
};

#endif //SIMULATION_H