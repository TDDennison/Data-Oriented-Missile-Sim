#include <exception>

#include "Simulation.h"

Simulation::Simulation()
{
    // Initialize the managers that MUST be around for the simulation to run the physics engine.
    accumulatorManager_ = AccumulatorManager::GetInstance();
    massManager_ = MassManager::GetInstance();
    movementManager_ = MovementManager::GetInstance();
    transformManager_ = TransformManager::GetInstance();

    clockManager_ = new ClockManager;
    testSoftwareManager_ = new TestSoftwareManager;
    loggingSystem_ = new LoggingSystem();

    // Get needed data from attributes.
    AttributesManager *attrManager = AttributesManager::GetInstance();
    maxTime_ = attrManager->GetAttribute<int>(Constants::SIMULATION_MAX_TIME);
    rate_ = attrManager->GetAttribute<double>(Constants::SIMULATION_TOP_RATE);
};

Simulation::~Simulation() 
{
    delete clockManager_;
    delete accumulatorManager_;
    delete massManager_;
    delete movementManager_;
    delete testSoftwareManager_;
    delete transformManager_;
    delete integrationSystem_;
    delete loggingSystem_;
}

void Simulation::Initialize()
{
    // Register systems.
    RegisterSystem_Booster(BoosterType::FIRST_STAGE);
    RegisterSystem_Booster(BoosterType::SECOND_STAGE);
    RegisterSystem_Earth();
    RegisterSystem_Integration();

    // Initialize systems
    InitializeLoggingSystem();
}

void Simulation::InitializeLoggingSystem()
{
    loggingSystem_->massManager = massManager_;
    loggingSystem_->movementManager = movementManager_;
    // loggingSystem.firstStageManager = &srmManager1;
    // loggingSystem.secondStageManager = &srmManager2;
    loggingSystem_->transformManager = transformManager_;
}

/**
 * @brief Register an Accumulator Component with the Accumulator Manager.
 * 
 * @note This method should only ever be called by the EntityManager class when entities are created.
*/
void Simulation::RegisterComponent_AccumulatorManager(Entity entity, AccumulatorComponent& accumulatorComponent)
{
    accumulatorManager_->Add(entity, accumulatorComponent);
}

/**
 * @brief Register a Mass Component with the Mass Manager.
 * 
 * @note This method should only ever be called by the EntityManager class when entities are created.
*/
void Simulation::RegisterComponent_MassManager(Entity entity, MassComponent& massComponent) {
    massManager_->Add(entity, massComponent);
}

/**
 * @brief Register a Movement Component with the Movement Manager.
 * 
 * @note This method should only ever be called by the EntityManager class when entities are created.
*/
void Simulation::RegisterComponent_MovementManager(Entity entity, MovementComponent& movementComponent) {
    movementManager_->Add(entity, movementComponent);
}

/**
 * @brief Register a Transform Component with the Transform Manager.
 * 
 * @note This method should only ever be called by the EntityManager class when entities are created.
*/
void Simulation::RegisterComponent_TransformManager(Entity entity, TransformComponent& transformComponent) {
    transformManager_->Add(entity, transformComponent);
}

void Simulation::RegisterComponent_ClockManager(Entity entity, ClockComponent& clockComponent)
{
    clockManager_->Add(entity, clockComponent);
}

// Register an entity with the Earth system.
void Simulation::RegisterEntity_EarthSystem(Entity entity)
{
    earthSystem_->RegisterEntity(entity);
}

// Register an entity with the first stage booster system.
void Simulation::RegisterEntity_FirstStageBoosterSystem(Entity entity, SolidRocketMotorComponent& srmComponent)
{   
    firstStageBoosterSystem_->AddSrmComponent(entity, srmComponent);
    firstStageBoosterSystem_->RegisterEntity(entity);
}

// Register an entity with the second stage booster system.
void Simulation::RegisterEntity_SecondStageBoosterSystem(Entity entity, SolidRocketMotorComponent& srmComponent)
{
    secondStageBoosterSystem_->RegisterEntity(entity);
    secondStageBoosterSystem_->AddSrmComponent(entity, srmComponent);
}

// Register an entity with the integration system.
void Simulation::RegisterEntity_IntegrationSystem(Entity entity)
{
    integrationSystem_->RegisterEntity(entity);
}

void Simulation::RegisterEntity_TestSoftwareSystem(Entity entity, SoftwareComponent& softwareComponent)
{
    testSoftwareSystem_->RegisterEntity(entity);
    testSoftwareSystem_->AddSoftwareComponent(entity, softwareComponent);
}

void Simulation::RegisterSystem_Booster(BoosterType type)
{
    SolidRocketMotorManager* srmManager = new SolidRocketMotorManager(type);
    BoosterSystem* boosterSystem = new BoosterSystem(type, accumulatorManager_, massManager_, movementManager_, srmManager, transformManager_, this);
    switch(type)
    {
        case BoosterType::FIRST_STAGE:
        {
            firstStageBoosterSystem_ = boosterSystem;
            break;
        }
        case BoosterType::SECOND_STAGE:
        {
            secondStageBoosterSystem_ = boosterSystem;
            break;
        }
    }

    // Add the system to the collection of systems.
    systems.push_back(boosterSystem);
}

// Register a new earth system using the given managers.
void Simulation::RegisterSystem_Earth()
{
    earthSystem_ = EarthSystem::GetInstance();

    // Add the system to the collection of systems.
    systems.push_back(earthSystem_);
}

void Simulation::RegisterSystem_Integration()
{
    // Set up the integration system based on inputs.
    AttributesManager *attrManager = AttributesManager::GetInstance();
    uint32_t integrationType = attrManager->GetAttribute<uint32_t>(Constants::INTEGRATION_SYSTEM_TYPE);
    switch(static_cast<IntegrationSystemType>(integrationType))
    {
        case IntegrationSystemType::EULER:
        {
            integrationSystem_ = new IntegrationSystem_Euler(accumulatorManager_, massManager_, movementManager_, transformManager_);
            break;
        }
        case IntegrationSystemType::RUNGE_KUTTA_2:
        {
            throw std::invalid_argument("Runge-Kutta 2 integration system has not yet been developed.");
            break;
        }
        case IntegrationSystemType::RUNGE_KUTTA_4:
        {
            throw std::invalid_argument("Runge-Kutta 4 integration system has not yet been developed.");
            break;
        }
        default:
        {
            throw std::invalid_argument("Integration system has not been defined in input set.");
            break;
        }
    }
}

void Simulation::RegisterSystem_TestSoftwareSystem()
{
    testSoftwareSystem_ = new TestSoftwareSystem(clockManager_, testSoftwareManager_);

    // Add the system to the collection of systems.
    systems.push_back(testSoftwareSystem_);
}

void Simulation::Update()
{
    std::cout << "In simulation update" << std::endl;
    // Initialize all of the systems.
    for (System *system : systems)
    {
        system->Initialize();
    }

    // Sort the systems based on user defined execution order.
    std::sort(systems.begin(), systems.end(), System::compareExecutionOrder);

    // Tell the systems to update
    real time = 0.0;
    double dt = 1.0 / (double)rate_;
    while (time <= maxTime_ + dt) // + dt to get the final timestep logged.
    {
        // Update all of the systems whose execution order can change.
        for (System *system : systems)
        {
            system->Update(dt);
        }
        
        integrationSystem_->Update(dt);

        std::cout << "===== Time: " << time << " =====" << std::endl;
        // Tell the systems to log their data.
        //loggingSystem_->WriteAllLogs(time);

        testSoftwareSystem_->Update(dt);
        clockManager_->UpdateClocks(dt);
        time += dt;

    }
}
