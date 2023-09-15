#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "Entity.h"
#include "Core/ILoggable.h"
#include "Components/SolidRocketMotorComponent.h"
#include "Components/SoftwareComponent.h"
#include "Managers/ClockManager.h"
#include "Managers/MassManager.h"
#include "Managers/Managers.h"
#include "Managers/MovementManager.h"
#include "Managers/TestSoftwareManager.h"
#include "Managers/TransformManager.h"
#include "Systems/BoosterSystems/FirstStageBoosterSystem.h"
#include "Systems/BoosterSystems/SecondStageBoosterSystem.h"
#include "Systems/EarthSystem.h"
#include "Systems/IntegrationSystem_Euler.h"
#include "Systems/IntegrationSystem_RK4.h"
#include "Systems/LoggingSystem.h"
#include "Systems/TestSoftwareSystem.h"

class FirstStageBoosterSystem;
class SecondStageBoosterSystem;

// Singleton class manages the executive level of communication between systems, managers and components.
class Simulation
{
    typedef std::vector<System*> SystemCollection;
    typedef std::vector<ILoggable*> LoggableCollection;

    public:
    inline static Simulation* GetInstance() {
        if(instance == nullptr) { instance = new Simulation(); }
        return instance;
    }
    ~Simulation();

    void Initialize();

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

    void Run();
    void Update();

    private:
    
    // Private constructor used to facilitate the singleton design pattern.
    Simulation();

    void ComputeCGs();
    void ComputeCG(MassComponent &massComponent);

    // Creates missile entities and their components.
    void CreateMissiles();

    // Creates a clock component for a missile entity at the beginning of the simulation run.
    void CreateClockComponent(Entity &entity);

    // Creates the first stage booster components at the beginning of the simulation run.
    SolidRocketMotorComponent& CreateFirstStageBoosterComponent(Entity &entity);

    // Creates the second stage booster components at the beginning of the simulation run.
    SolidRocketMotorComponent& CreateSecondStageBoosterComponent(Entity &entity);

    // Creates a software component at the beginning of the simulation run.
    void CreateTestSoftwareComponent(Entity &entity);

    // Private instance of the Simulation class used to facilitate the singleton design pattern.
    inline static Simulation* instance = nullptr;

    void RegisterSystem_FirstStageBooster();
    void RegisterSystem_SecondStageBooster();
    void RegisterSystem_Earth();
    void RegisterSystem_Integration();
    void RegisterSystem_TestSoftwareSystem();

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
    LoggableCollection loggables{};

    AccumulatorManager* accumulatorManager_              = nullptr;
    ClockManager* clockManager_                          = nullptr;
    MassManager* massManager_                            = nullptr;
    MovementManager* movementManager_                    = nullptr;
    TestSoftwareManager* testSoftwareManager_            = nullptr;
    TransformManager* transformManager_                  = nullptr;
    FirstStageBoosterSystem* firstStageBoosterSystem_    = nullptr;
    SecondStageBoosterSystem* secondStageBoosterSystem_  = nullptr;
    EarthSystem* earthSystem_                            = nullptr;
    System* integrationSystem_                           = nullptr;
    LoggingSystem* loggingSystem_                        = nullptr;
    TestSoftwareSystem* testSoftwareSystem_              = nullptr;
};

#endif //SIMULATION_H