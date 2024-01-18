#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "Entity.h"
#include "ILoggable.h"
#include "SolidRocketMotorComponent.h"
#include "SoftwareComponent.h"

#include "ClockManager.h"
#include "DomSimConstants.h"
#include "MassManager.h"
#include "ManagersConstants.h"
#include "MovementManager.h"
#include "TestSoftwareManager.h"
#include "TransformManager.h"

#include "FirstStageBoosterSystem.h"
#include "SecondStageBoosterSystem.h"
#include "EarthSystem.h"
#include "IIntegrationSystem.h"
#include "IntegrationSystem_Euler.h"
#include "IntegrationSystem_RK4.h"
#include "BinaryLogger.h"
#include "TestSoftwareSystem.h"

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

    void PostProcessOutput();
    void Run();

    private:
    
    // Private constructor used to facilitate the singleton design pattern.
    Simulation();

    void Update();

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

    // Handles registering any queued components between frames.
    void HandleQueuedComponents();

    // Handles registering any queued entities between frames.
    void HandleQueuedEntities();

    void Initialize();

    void RegisterComponent_AccumulatorManager(AccumulatorComponent&);
    void RegisterComponent_ClockManager(ClockComponent&);
    void RegisterComponent_FirstStageSrm(SolidRocketMotorComponent&);
    void RegisterComponent_MassManager(MassComponent&);
    void RegisterComponent_MovementManager(MovementComponent&);
    void RegisterComponent_SecondStageSrm(SolidRocketMotorComponent&);
    void RegisterComponent_TestSoftwareManager(SoftwareComponent&);
    void RegisterComponent_TransformManager(TransformComponent&);
    
    void RegisterEntity_EarthSystem(Entity);
    void RegisterEntity_FirstStageBoosterSystem(Entity);
    void RegisterEntity_IntegrationSystem(Entity);
    void RegisterEntity_SecondStageBoosterSystem(Entity);
    void RegisterEntity_TestSoftwareSystem(Entity);

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

            attributesManager->AddAttribute<uint32_t>(DomSim::Constants::INTEGRATION_SYSTEM_TYPE, Core::Enumerations::AttributeType::UINT32, DomSim::Constants::DEFAULT_UINT8);
            attributesManager->AddAttribute<int>(DomSim::Constants::SIMULATION_MAX_TIME, Core::Enumerations::AttributeType::INT32, DomSim::Constants::DEFAULT_INT32);
            attributesManager->AddAttribute<double>(DomSim::Constants::SIMULATION_TOP_RATE, Core::Enumerations::AttributeType::DOUBLE, DomSim::Constants::DEFAULT_DOUBLE);
        }
    };

    inline static const Attributes attributes_{}; // Static constructor used to register attributes before main() is started.
    
    // The maximum amount of time the simulation will run for before ending.
    // Set this property using the input file attributes.
    int maxTime_ = 0;

    // The frequency that the simulation runs at.
    // Set this property using the input file attributes.
    double rate_ = 0.0;

    // Private instance of the Simulation class used to facilitate the singleton design pattern.
    inline static Simulation* instance = nullptr;

    // Collection of system pointers used to enforce order of execution.
    SystemCollection systems{};
    LoggableCollection loggables{};

    AccumulatorManager* accumulatorManager_              = nullptr;
    ClockManager* clockManager_                          = nullptr;
    MassManager* massManager_                            = nullptr;
    MovementManager* movementManager_                    = nullptr;
    TransformManager* transformManager_                  = nullptr;

    TestSoftwareManager* testSoftwareManager_            = nullptr;

    FirstStageBoosterSystem* firstStageBoosterSystem_    = nullptr;
    SecondStageBoosterSystem* secondStageBoosterSystem_  = nullptr;
    EarthSystem* earthSystem_                            = nullptr;
    IIntegrationSystem* integrationSystem_                = nullptr;
    TestSoftwareSystem* testSoftwareSystem_              = nullptr;
};

#endif //SIMULATION_H