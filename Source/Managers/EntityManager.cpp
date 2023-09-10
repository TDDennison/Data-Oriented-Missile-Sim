#include <string>

#include "EntityManager.h"

#include "../Entity.h"
#include "../Simulation.h"

#include "../Components/AccumulatorComponent.h"
#include "../Components/MassComponents/MassComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/Utilities.h"

Entity EntityManager::CreateEntity()
{
    Entity entity = { nextId };
    ++nextId;

    // Register create the new entity's minimal components and register them with their appropriate managers.
    AccumulatorComponent accumulatorComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::NONE));
    MassComponent massComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::NONE));
    MovementComponent movementComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::NONE));
    TransformComponent transformComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::NONE));

    Simulation *simulation = Simulation::GetInstance();

    // Register entity components with default managers.
    simulation->RegisterComponent_AccumulatorManager(entity, accumulatorComponent);
    simulation->RegisterComponent_MassManager(entity, massComponent);
    simulation->RegisterComponent_MovementManager(entity, movementComponent);
    simulation->RegisterComponent_TransformManager(entity, transformComponent);

    // Register entity with default systems.
    simulation->RegisterEntity_EarthSystem(entity);
    simulation->RegisterEntity_IntegrationSystem(entity);

    return entity;
};