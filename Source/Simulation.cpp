#include <exception>
#include <memory>
#include <vector>

#include "Simulation.h"
#include "Components/Utilities.h"
#include "Core/Configurations.h"

#include "Parsers/BinaryFileParser/BinaryFileParser.h"

Simulation::Simulation()
{
    // Initialize the managers that MUST be around for the simulation to run the physics engine.
    accumulatorManager_ = AccumulatorManager::GetInstance();
    loggables.push_back(accumulatorManager_);

    massManager_ = MassManager::GetInstance();
    loggables.push_back(massManager_);

    movementManager_ = MovementManager::GetInstance();
    loggables.push_back(movementManager_);
    
    transformManager_ = TransformManager::GetInstance();
    loggables.push_back(transformManager_);

    clockManager_ = new ClockManager();
    loggables.push_back(clockManager_);

    testSoftwareManager_ = new TestSoftwareManager();
    loggables.push_back(testSoftwareManager_);
    
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
    RegisterSystem_FirstStageBooster();
    RegisterSystem_SecondStageBooster();
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
void Simulation::RegisterSystem_FirstStageBooster()
{
    // Create the SRM Manager and register it with the loggables collection.

    SolidRocketMotorManager* srmManager = new SolidRocketMotorManager(Constants::LOG_FILE_FIRST_STAGE_SRM_MANAGER, BoosterType::FIRST_STAGE);
    loggables.push_back(srmManager);

    firstStageBoosterSystem_ = new FirstStageBoosterSystem(accumulatorManager_, massManager_, movementManager_, srmManager, transformManager_, this);

    // Add the system to the collection of systems.
    systems.push_back(firstStageBoosterSystem_);
}

/**
 * @brief Register a new booster system with the Simulation.
 * @param[in] type: The type of the booster system to register.
 * @note This method should only ever be called by the Simulation class to set up the minimum necessary systems to simulate the missile.
*/
void Simulation::RegisterSystem_SecondStageBooster()
{
    // Create the SRM Manager and register it with the loggables collection.

    SolidRocketMotorManager* srmManager = new SolidRocketMotorManager("SecondStageSrmManager", BoosterType::SECOND_STAGE);
    loggables.push_back(srmManager);

    secondStageBoosterSystem_ = new SecondStageBoosterSystem(accumulatorManager_, massManager_, movementManager_, srmManager, transformManager_, this);

    // Add the system to the collection of systems.
    systems.push_back(secondStageBoosterSystem_);
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
            integrationSystem_ = new IntegrationSystem_RK4(accumulatorManager_, massManager_, movementManager_, transformManager_);
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
    std::vector<std::pair<float, float>> missileLocations = Configurations::GetInstance()->GetMissileStartingLocations();
    std::cout << "There are " << missileLocations.size() << " missile locations parsed." << std::endl;

    // TODO: Convert the lat/lon pairs into ECI positions/orientations to use for instantiating missile properties here.
    for (auto location : missileLocations)
    {
        std::cout << location.first << " " << location.second << std::endl;
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

        // First stage mass.
        MassComponent fsMass(ComponentUtilities::CreateComponentId(missileEntity.id, ComponentUtilities::FIRST_STAGE_SRM));
        fsMass.mass += firstStageComponent.inertMass + firstStageComponent.propellantMass;
        ComputeCG(fsMass);
        missileMass.AddSubmass(ComponentUtilities::ComponentDesignators::FIRST_STAGE_SRM, fsMass);

        // Second stage mass.
        MassComponent ssMass(ComponentUtilities::CreateComponentId(missileEntity.id, ComponentUtilities::SECOND_STAGE_SRM));
        ssMass.mass += secondStageComponent.inertMass + secondStageComponent.propellantMass;
        ComputeCG(ssMass);
        missileMass.AddSubmass(ComponentUtilities::ComponentDesignators::SECOND_STAGE_SRM, ssMass);







        // Set up the position of the missile. This is the position in the ECI frame of the origin of the missile-station frame.
        TransformComponent &missileTrans = transformManager_->Lookup(missileEntity);

        // TODO: CONVERT LAT/LON LOCATION TO ECI AND COMPUTE ORIENTATION HERE.
        Vector3 position_ecef = HelperMethods::LLAtoECEF(location.first, location.second, 0.0); // Position always starts on the surface of the earth.

        missileTrans.position_eci = position_ecef; // ECI and ECEF are inline prior to the start of the simulation run.
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
}

SolidRocketMotorComponent& Simulation::CreateFirstStageBoosterComponent(Entity &entity)
{
    // Set up the first booster's physical properties
    SolidRocketMotorComponent *srmComponent = new SolidRocketMotorComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::FIRST_STAGE_SRM));

    // TODO: Have these values come from the input files in the SolidRocketMotorComponent class.
    srmComponent->thrust = 1000.0;
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
    // Initialize all of the systems.
    for (System *system : systems)
    {
        system->Initialize();
    }

    // Sort the systems based on user defined execution order.
    std::sort(systems.begin(), systems.end(), System::compareExecutionOrder);

    // Tell the systems to update
    float time = 0.0;
    float dt = 1.0 / (float)rate_;
    float dtOut = 0.0;
    bool shouldLog = false;
    while (time <= maxTime_ + dt) // + dt to get the final timestep logged.
    {
        // Order of execution for systems
        // 1) Integration System
        // 2) Physics systems
        // 3) Software systems
        // 4) Integration system

        integrationSystem_->Update(dt, dtOut, shouldLog);

        //std::cout << "===== Time: " << std::setprecision(8) << time << " =====" << std::endl;

        // 2) Physics systems.
        // ==================================================
        //earthSystem_->Update(dt); // Earth system should always run with the physics systems, in no particular order.

        // Update all of the systems whose execution order can change.
        for (System *system : systems)
        {
            system->Update(dt);
        }

        // 3) Software systems.
        // ==================================================
        testSoftwareSystem_->Update(dt);

        // NOTE: I DON"T THINK THIS NEEDS TO BE DONE IN EVERY FRAME. THAT WOULD DEPEND ON THE TYPE OF INTEGRATION SYSTEM
        // RK4 MASS STAYS THE SAME FOR THE MIDDLE TWO FRAMES.
        // Update CG positions and inertia tensors based on burned mass 
        // The integration system accounts for moving the cg position along with the missile position
        // based on forces. This accounts for moving the cg position in the missile station frame based
        // on burned mass.
        ComputeCGs();


        // Log all necessary data.
        // ==================================================
        if (shouldLog)
        {
            for (auto loggable : loggables)
            {
                loggable->WriteToLog(&time);
            }
        }


        // Finally update the time management components.
        clockManager_->UpdateClocks(dtOut);
        time += dtOut;

    }

    // The simulation has reached the end.
    // Finalize necessary components.
    for (auto loggable : loggables)
    {
        loggable->FinalizeLog();
    }

    // After the simulation has ended and all data has been logged, begin the post-processing operations
    for (auto loggable : loggables)
    {
        loggable->PostProcessLog(PostProcessLogType::TEXT);
    }
}


void Simulation::ComputeCGs()
{
    unsigned int numComponents = 0;
    MassComponent *massComponentsStart = massManager_->GetComponentData(numComponents);

    for (unsigned int i = 0; i < numComponents; ++i)
    {
        MassComponent &component = *(massComponentsStart + i);
        Vector3 mass_moment_arms = Vector3::Zero();
        if (!component.subMasses.empty())
        {
            component.position_cg_body = Vector3::Zero();
            for (auto key : component.subMasses)
            {
                MassComponent &subMass = key.second;
                // Don't compute cg unless it has changed since previously computed.
                if (key.second.hasChanged)
                {
                    ComputeCG(key.second);
                }

                // Translate object cg to missile frame.
                Vector3 pos_cg_missile_frame = subMass.position_cg_body + Configurations::GetInstance()->GetObjectOffset(subMass.getComponentId());
                Vector3 mass_moment_arm = pos_cg_missile_frame * subMass.mass;

                // position_cg_body is equivalent to position_cg_missile frame here for the aggregate component.
                mass_moment_arms += mass_moment_arm;
            }

            component.position_cg_body = (mass_moment_arms * (1.0 / component.mass));
        }
        else // The component is not made of other masses.
        {
            if(component.hasChanged)
            {
                ComputeCG(component);
            }
        }
    }
}

void Simulation::ComputeCG(MassComponent &massComponent)
{
    uint8_t componentId = massComponent.getComponentId();
    Vector3 pos_cg_obj = Configurations::GetInstance()->GetObjectGeometry(componentId);

    // Assume CG is at the center of the geometric shape.
    massComponent.position_cg_body = pos_cg_obj * 0.5;
}
