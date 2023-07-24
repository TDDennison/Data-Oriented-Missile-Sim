#include "Simulation.h"

Simulation::Simulation()
{
    // Initialize the managers that MUST be around for the simulation to run the physics engine.
    // TODO: Consider making these singletons.
    clockManager_ = new ClockManager;
    massManager_ = new MassManager;
    movementManager_ = new MovementManager;
    transformManager_ = new TransformManager;
    testSoftwareManager_ = new TestSoftwareManager;

    accumulatorManager_ = new AccumulatorManager(massManager_, transformManager_);

    loggingSystem_ = new LoggingSystem();

    // Get needed data from attributes.
    AttributesManager *attrManager = AttributesManager::GetInstance();
    maxTime_ = attrManager->GetAttribute<int>(Constants::SIMULATION_MAX_TIME);
    rate_ = attrManager->GetAttribute<int>(Constants::SIMULATION_TOP_RATE);
};

Simulation::~Simulation() 
{
    delete clockManager_;
    delete accumulatorManager_;
    delete massManager_;
    delete movementManager_;
    delete testSoftwareManager_;
    delete transformManager_;
    delete loggingSystem_;
}

void Simulation::Initialize()
{
    RegisterSystem_Booster(BoosterType::FIRST_STAGE);
    RegisterSystem_Booster(BoosterType::SECOND_STAGE);

    RegisterSystem_Earth();
    RegisterSystem_Integration();

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

void Simulation::RegisterComponent_AccumulatorManager(Entity entity, AccumulatorComponent& accumulatorComponent)
{
    accumulatorManager_->Add(entity, accumulatorComponent);
}

void Simulation::RegisterComponent_ClockManager(Entity entity, ClockComponent& clockComponent)
{
    clockManager_->Add(entity, clockComponent);
}

void Simulation::RegisterComponent_MassManager(Entity entity, MassComponent& massComponent) {
    massManager_->Add(entity, massComponent);
}

void Simulation::RegisterComponent_MovementManager(Entity entity, MovementComponent& movementComponent) {
    movementManager_->Add(entity, movementComponent);
}

void Simulation::RegisterComponent_TransformManager(Entity entity, TransformComponent& transformComponent) {
    transformManager_->Add(entity, transformComponent);
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
}

// Register a new earth system using the given managers.
void Simulation::RegisterSystem_Earth()
{
    earthSystem_ = new EarthSystem(*accumulatorManager_, *massManager_, *transformManager_);
}

void Simulation::RegisterSystem_Integration()
{
    integrationSystem_ = new IntegrationSystem_Euler(accumulatorManager_, massManager_, movementManager_, transformManager_);
}

void Simulation::RegisterSystem_TestSoftwareSystem()
{
    testSoftwareSystem_ = new TestSoftwareSystem(clockManager_, testSoftwareManager_);
}

void Simulation::Update()
{
    // Tell the systems to update
    real time = 0.0;
    double dt = 1.0 / (double)rate_;
    while (time <= maxTime_)
    {
        firstStageBoosterSystem_->Update(dt);
        secondStageBoosterSystem_->Update(dt);
        earthSystem_->Update(dt);
        integrationSystem_->Update(dt);

        std::cout << "===== Time: " << time << " =====" << std::endl;
        // Tell the systems to log their data.
        //loggingSystem_->WriteAllLogs(time);

        testSoftwareSystem_->Update(dt);
        clockManager_->UpdateClocks(dt);
        time += dt;

    }
}
