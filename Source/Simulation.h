#ifndef SIMULATION_H
#define SIMULATION_H

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

    void Update(real dt);

    private:
    AccumulatorManager* accumulatorManager_;
    ClockManager* clockManager_;
    MassManager* massManager_;
    MovementManager* movementManager_;
    TestSoftwareManager* testSoftwareManager_;
    TransformManager* transformManager_;
    BoosterSystem* firstStageBoosterSystem_;
    BoosterSystem* secondStageBoosterSystem_;
    EarthSystem* earthSystem_;
    IntegrationSystem_Euler* integrationSystem_;
    LoggingSystem* loggingSystem_;
    TestSoftwareSystem* testSoftwareSystem_;
};

#endif //SIMULATION_H