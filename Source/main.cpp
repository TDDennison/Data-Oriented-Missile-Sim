#include <chrono>
#include <iostream>

#include "Components/AccumulatorComponent.h"
#include "Components/MovementComponent.h"
#include "Components/TransformComponent.h"
#include "Components/Utilities.h"

#include "Core/Configurations.h"

#include "Managers/AccumulatorManager.h"
#include "Managers/EntityManager.h"
#include "Managers/Managers.h"

#include "Parsers/CommandLineParser/CommandLineParser.h"
#include "Parsers/InputFileParser/InputFileParser.h"

#include "Systems/BoosterSystem.h"
#include "Systems/LoggingSystem.h"
#include "Systems/IntegrationSystem_Euler.h"

void CreateBoosterWithPayload();

int main(int argc, char** argv)
{
    std::cout << "Data Oriented Missile Simulation running!" << std::endl;

    // Create a vector of strings from the command line arguments.
    std::vector<std::string> cmdArgs(argv+1, argv + argc); // Remove the first argument as it is the arg calling this function.

    // Try to parse the command line arguments.
    CommandLineParser commandLineParser;
    bool parseSucceeded = commandLineParser.TryParse(argc-1, argv+1);
    if(!parseSucceeded) { return 1; }

    #ifdef RUN_UNIT_TESTS

    #include "_UnitTests/_unitTests.h"

    UnitTests::RunAllTests();

    #else // Run the program for analysis

    // Validate the run configurations.
    std::pair<bool, std::string> configurationsValid = Configurations::GetInstance()->ValidateConfigurations();
    if(!configurationsValid.first)
    {
        std::cout << configurationsValid.second << std::endl;
        return 1;
    }

    // Parse the input file.
    InputFileParser inFileParser(Configurations::GetInstance()->GetInputFilePath());

    auto start = std::chrono::high_resolution_clock::now();

    CreateBoosterWithPayload();

    auto finish = std::chrono::high_resolution_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(finish-start);

    std::cout << "Time elapsed: " << milliseconds.count() << " milliseconds." << std::endl;

    #endif //RUN_UNIT_TESTS

    return 0;
}

// Trying to figure out how to aggregate masses and decrement individuals masses as well.
void CreateBoosterWithPayload()
{
    LoggingSystem loggingSystem;

    // Create the simulation object.
    Simulation simulation;
    simulation.Initialize();

    // One entity per physical object and one entity for the abstract aggregate object?
    Entity abstractMissile1 = EntityManager::CreateEntity();
    Entity abstractMissile2 = EntityManager::CreateEntity();

    AccumulatorComponent accumComp1;
    ComponentUtilities::SetComponentId(accumComp1, abstractMissile1.id, ComponentUtilities::ACCUMULATOR);
    simulation.RegisterComponent_AccumulatorManager(abstractMissile1, accumComp1);

    AccumulatorComponent accumComp2;
    ComponentUtilities::SetComponentId(accumComp2, abstractMissile2.id, ComponentUtilities::ACCUMULATOR);
    simulation.RegisterComponent_AccumulatorManager(abstractMissile2, accumComp2);

    // ===========================================

    // Set up the first booster's physical properties
    SolidRocketMotorComponent srmComponent11;
    srmComponent11.thrust = 100.0;
    srmComponent11.inertMass = 400.0;
    srmComponent11.propellantMass = 100.0;

    ComponentUtilities::SetComponentId(srmComponent11, abstractMissile1.id, ComponentUtilities::FIRST_STAGE_SRM);
    simulation.RegisterEntity_FirstStageBoosterSystem(abstractMissile1, srmComponent11);

    // ============================================

    // Set up the first booster's physical properties
    SolidRocketMotorComponent srmComponent21;
    srmComponent21.thrust = 100.0;
    srmComponent21.inertMass = 400.0;
    srmComponent21.propellantMass = 30.0;

    ComponentUtilities::SetComponentId(srmComponent21, abstractMissile2.id, ComponentUtilities::FIRST_STAGE_SRM);
    simulation.RegisterEntity_SecondStageBoosterSystem(abstractMissile2, srmComponent21);

    // ============================================

    // Set up the second booster's physical properties
    SolidRocketMotorComponent srmComponent12;
    srmComponent12.thrust = 100.0;
    srmComponent12.inertMass = 400.0;
    srmComponent12.propellantMass = 100.0;

    // =============================================

    // Set up the aggregate physical properties
    MassComponent aggregateMass1;
    aggregateMass1.mass = srmComponent11.inertMass + srmComponent11.propellantMass + srmComponent12.inertMass + srmComponent12.propellantMass;

    TransformComponent aggregateTrans1;
    aggregateTrans1.position_eci = {1000000.0, 0.0, 0.0};

    MovementComponent aggregateMovement1;
    aggregateMovement1.velocity_eci = {0.0, 0.0, 0.0};
    aggregateMovement1.acceleration_eci = {0.0, 0.0, 0.0};

    ComponentUtilities::SetComponentId(aggregateMass1, abstractMissile1.id, ComponentUtilities::AGGREGATE);
    ComponentUtilities::SetComponentId(aggregateTrans1, abstractMissile1.id, ComponentUtilities::AGGREGATE);
    ComponentUtilities::SetComponentId(aggregateMovement1, abstractMissile1.id, ComponentUtilities::AGGREGATE);

    simulation.RegisterComponent_MassManager(abstractMissile1, aggregateMass1);
    simulation.RegisterComponent_MovementManager(abstractMissile1, aggregateMovement1);
    simulation.RegisterComponent_TransformManager(abstractMissile1, aggregateTrans1);

    simulation.RegisterEntity_EarthSystem(abstractMissile1);
    simulation.RegisterEntity_IntegrationSystem(abstractMissile1);

    // ============================================
    MassComponent aggregateMass2;
    aggregateMass2.mass = srmComponent21.inertMass + srmComponent21.propellantMass;

    TransformComponent aggregateTrans2;
    aggregateTrans2.position_eci = {1000000.0, 0.0, 0.0};

    MovementComponent aggregateMovement2;
    aggregateMovement2.velocity_eci = {0.0, 0.0, 0.0};
    aggregateMovement2.acceleration_eci = {0.0, 0.0, 0.0};

    ComponentUtilities::SetComponentId(aggregateMass2, abstractMissile2.id, ComponentUtilities::AGGREGATE);
    ComponentUtilities::SetComponentId(aggregateTrans2, abstractMissile2.id, ComponentUtilities::AGGREGATE);
    ComponentUtilities::SetComponentId(aggregateMovement2, abstractMissile2.id, ComponentUtilities::AGGREGATE);

    simulation.RegisterComponent_MassManager(abstractMissile2, aggregateMass2);
    simulation.RegisterComponent_MovementManager(abstractMissile2, aggregateMovement2);
    simulation.RegisterComponent_TransformManager(abstractMissile2, aggregateTrans2);

    simulation.RegisterEntity_EarthSystem(abstractMissile2);
    simulation.RegisterEntity_IntegrationSystem(abstractMissile2);

    simulation.RegisterSystem_TestSoftwareSystem();

    SoftwareComponent testSoftwareComponent;
    testSoftwareComponent.executionFrequency = 0.05;
    simulation.RegisterEntity_TestSoftwareSystem(abstractMissile1, testSoftwareComponent);

    ClockComponent clockComponent;
    clockComponent.time = 0.0;
    simulation.RegisterComponent_ClockManager(abstractMissile1, clockComponent);

    float dt = 1.0 / 500.0;
    simulation.Update(dt);
};

