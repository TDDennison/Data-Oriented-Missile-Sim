#include <exception>

#include "Simulation.h"
#include "Components/Utilities.h"

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
    RegisterSystem_TestSoftwareSystem();


    // Finally, create the missile objects.
    CreateMissiles();
}

/**
 * @brief Register an Accumulator Component with the Accumulator Manager.
 * @param[in] entity: The entity used as an identifier for the component data.
 * @param[in] accumulatorComponent: The component data to be managed.
 * @note This method should only ever be called by the EntityManager class when entities are created.
*/
void Simulation::RegisterComponent_AccumulatorManager(Entity entity, AccumulatorComponent& accumulatorComponent)
{
    accumulatorManager_->Add(entity, accumulatorComponent);
}

/**
 * @brief Register a Mass Component with the Mass Manager.
 * @param[in] entity: The entity used as an identifier for the component data.
 * @param[in] massComponent: The component data to be managed.
 * @note This method should only ever be called by the EntityManager class when entities are created.
*/
void Simulation::RegisterComponent_MassManager(Entity entity, MassComponent& massComponent) {
    massManager_->Add(entity, massComponent);
}

/**
 * @brief Register a Movement Component with the Movement Manager.
 * @param[in] entity: The entity used as an identifier for the component data.
 * @param[in] movementComponent: The component data to be managed.
 * @note This method should only ever be called by the EntityManager class when entities are created.
*/
void Simulation::RegisterComponent_MovementManager(Entity entity, MovementComponent& movementComponent) {
    movementManager_->Add(entity, movementComponent);
}

/**
 * @brief Register a Transform Component with the Transform Manager.
 * @param[in] entity: The entity used as an identifier for the component data.
 * @param[in] transformComponent: The component data to be managed.
 * @note This method should only ever be called by the EntityManager class when entities are created.
*/
void Simulation::RegisterComponent_TransformManager(Entity entity, TransformComponent& transformComponent) {
    transformManager_->Add(entity, transformComponent);
}

/**
 * @brief Register a Clock Component with the Clock Manager.
 * @param[in] entity: The entity used as an identifier for the component data.
 * @param[in] clockComponent: The component data to be managed.
*/
void Simulation::RegisterComponent_ClockManager(Entity entity, ClockComponent& clockComponent)
{
    clockManager_->Add(entity, clockComponent);
}

/**
 * @brief Register an entity with the Earth System.
 * @param[in] entity: The entity to be manipulated by the system.
 * @note This method should only ever be called by the EntityManager class when entities are created.
*/
void Simulation::RegisterEntity_EarthSystem(Entity entity)
{
    earthSystem_->RegisterEntity(entity);
}

/**
 * @brief Register an entity with the First Stage Booster System.
 * @param[in] entity: The entity to be used as an identifier for component data and manipulated by the system.
 * @param[in] srmComponent: The SolidRocketMotorComponent object instance to be added to the system's SolidRocketMotorManager.
*/
void Simulation::RegisterEntity_FirstStageBoosterSystem(Entity entity, SolidRocketMotorComponent& srmComponent)
{   
    firstStageBoosterSystem_->AddSrmComponent(entity, srmComponent);
    firstStageBoosterSystem_->RegisterEntity(entity);
}

/**
 * @brief Register an entity with the Second Stage Booster System.
 * @param[in] entity: The entity to be used as an identifier for component data and manipulated by the system.
 * @param[in] srmComponent: The SolidRocketMotorComponent object instance to be added to the system's SolidRocketMotorManager.
*/
void Simulation::RegisterEntity_SecondStageBoosterSystem(Entity entity, SolidRocketMotorComponent& srmComponent)
{
    secondStageBoosterSystem_->RegisterEntity(entity);
    secondStageBoosterSystem_->AddSrmComponent(entity, srmComponent);
}

/**
 * @brief Register an entity with the Integration System.
 * @param[in] entity: The entity to be manipulated by the system.
 * @note This method should only ever be called by the EntityManager class when entities are created.
*/
void Simulation::RegisterEntity_IntegrationSystem(Entity entity)
{
    integrationSystem_->RegisterEntity(entity);
}

/**
 * @brief Register an entity with the Test Software System.
 * @param[in] entity: The entity to be used as an identifier for component data and manipulated by the system.
 * @param[in] softwareComponent: The SoftwareComponent object instance to be added to the system's SoftwareManager.
*/
void Simulation::RegisterEntity_TestSoftwareSystem(Entity entity, SoftwareComponent& softwareComponent)
{
    testSoftwareSystem_->RegisterEntity(entity);
    testSoftwareSystem_->AddSoftwareComponent(entity, softwareComponent);
}

/**
 * @brief Register a new booster system with the Simulation.
 * @param[in] type: The type of the booster system to register.
 * @note This method should only ever be called by the Simulation class to set up the minimum necessary systems to simulate the missile.
*/
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

/**
 * @brief Register a new Earth System with the Simulation.
 * @note This method should only ever be called by the Simulation class to set up the minimum necessary systems to simulate the missile.
*/
void Simulation::RegisterSystem_Earth()
{
    earthSystem_ = EarthSystem::GetInstance();

    // Add the system to the collection of systems.
    systems.push_back(earthSystem_);
}

/**
 * @brief Register a new Integration System with the Simulation.
 * @note This method should only ever be called by the Simulation class to set up the minimum necessary systems to simulate the missile.
*/
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

/**
 * @brief Register a new Test Software System with the Simulation.
 * @note This method should only ever be called by the Simulation class to set up the minimum necessary systems to simulate the missile.
*/
void Simulation::RegisterSystem_TestSoftwareSystem()
{
    testSoftwareSystem_ = new TestSoftwareSystem(clockManager_, testSoftwareManager_);

    // Add the system to the collection of systems.
    systems.push_back(testSoftwareSystem_);
}

void Simulation::CreateMissiles()
{
    // Create the abstract missile entity.
    Entity missileEntity = EntityManager::CreateEntity();

    // Create the first stage booster.
    SolidRocketMotorComponent &firstStageComponent = CreateFirstStageBoosterComponent(missileEntity);
    RegisterEntity_FirstStageBoosterSystem(missileEntity, firstStageComponent);

    // Create the second stage booster. 
    // NOTE: DO NOT REGISTER THE ENTITY WITH THE SECOND STAGE SYSTEM!
    //       THIS HAPPENS AFTER THE FIRST STAGE HAS BURNED OUT AND SEPARATED.
    SolidRocketMotorComponent &secondStageComponent = CreateSecondStageBoosterComponent(missileEntity);




    // Aggregate the total mass of the missile.
    MassComponent &missileMass = massManager_->Lookup(missileEntity);
    missileMass.mass += firstStageComponent.inertMass + firstStageComponent.propellantMass;
    missileMass.mass += secondStageComponent.inertMass + secondStageComponent.propellantMass;

    // Set up the position of the missile. This is the position in the ECI frame of the origin of the missile-station frame.
    TransformComponent &missileTrans = transformManager_->Lookup(missileEntity);
    missileTrans.position_eci = {1000000.0, 0.0, 0.0}; // TODO: THIS NEEDS TO BE PASSED INTO THIS FUNCTION AND RETREIVED FROM THE INPUT FILES.
    missileTrans.orientation_eci = {1.0, 1.0, 1.0, 1.0}; // TODO: THIS NEEDS TO BE CALCULATED FROM THE POSITION. THE MISSILE SHOULD BE ORIENTED NORMAL TO THE SURFACE OF THE EARTH.

    // Set up the acceleration and velocity of the missile.
    MovementComponent &missileMovement = movementManager_->Lookup(missileEntity);
    missileMovement.velocity_eci = {0.0, 0.0, 0.0};
    missileMovement.angular_velocity_eci = {0.0, 0.0, 0.0};
    missileMovement.acceleration_eci = {0.0, 0.0, 0.0};
    missileMovement.angular_acceleration_eci = {0.0, 0.0, 0.0};


    // Create the test software component. 
    // TODO: THIS IS JUST FOR TESTING. THIS SHOULD BE REMOVED WHEN NECESSARY
    CreateTestSoftwareComponent(missileEntity);

    // Create the clock component for the missile.
    CreateClockComponent(missileEntity);
}

SolidRocketMotorComponent& Simulation::CreateFirstStageBoosterComponent(Entity &entity)
{
    // Set up the first booster's physical properties
    SolidRocketMotorComponent *srmComponent = new SolidRocketMotorComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::FIRST_STAGE_SRM));

    // TODO: Have these values come from the input files in the SolidRocketMotorComponent class.
    srmComponent->thrust = 100.0;
    srmComponent->inertMass = 400.0;
    srmComponent->propellantMass = 100.0;

    return *srmComponent;
}

SolidRocketMotorComponent& Simulation::CreateSecondStageBoosterComponent(Entity &entity)
{
    // Set up the first booster's physical properties
    SolidRocketMotorComponent *srmComponent = new SolidRocketMotorComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::SECOND_STAGE_SRM));

    // TODO: Have these values come from the input files in the SolidRocketMotorComponent class.
    srmComponent->thrust = 100.0;
    srmComponent->inertMass = 400.0;
    srmComponent->propellantMass = 100.0;

    return *srmComponent;
}

void Simulation::CreateTestSoftwareComponent(Entity &entity)
{
    SoftwareComponent testSoftwareComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::TEST_SOFTWARE));
    testSoftwareComponent.executionFrequency = 0.05;
    RegisterEntity_TestSoftwareSystem(entity, testSoftwareComponent);
}

void Simulation::CreateClockComponent(Entity &entity)
{
    ClockComponent clockComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::CLOCK));
    clockComponent.time = 0.0;
    RegisterComponent_ClockManager(entity, clockComponent);
}

void Simulation::Run()
{
    Initialize();
    Update();
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
        // Order of execution for systems
        // 1) Logging system
        // 2) Physics systems
        // 3) Software systems
        // 4) Integration system

        // 1) Logging system.
        // ==================================================
        std::cout << "===== Time: " << time << " =====" << std::endl;
        // Tell the systems to log their data.
        loggingSystem_->WriteAllLogs(time);

        // 2) Physics systems.
        // ==================================================
        earthSystem_->Update(dt); // Earth system should always run with the physics systems, in no particular order.

        // Update all of the systems whose execution order can change.
        for (System *system : systems)
        {
            system->Update(dt);
        }

        // 3) Software systems.
        // ==================================================
        
        // 4) Integration systems
        // ==================================================
        integrationSystem_->Update(dt);

        testSoftwareSystem_->Update(dt);
        clockManager_->UpdateClocks(dt);
        time += dt;

    }
}
