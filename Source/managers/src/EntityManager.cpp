#include <string>

#include "EntityManager.h"

#include "Entity.h"

#include "AccumulatorComponent.h"
#include "DomSimEnumerations.h"
#include "MassComponent.h"
#include "MovementComponent.h"
#include "SolidRocketMotorComponent.h"
#include "TransformComponent.h"
#include "Utilities.h"


EntityManager* EntityManager::GetInstance() {
    if(instance == nullptr) { instance = new EntityManager(); }
    return instance;
}

// Creates an entity from scratch. This should not be used when creating entities from separating components.
// The CreateEntityFrom() method should be used in that case.
Entity EntityManager::CreateEntity()
{
    Entity entity{ nextId };
    ++nextId;

    // Create the new entity's minimal components and register them with their appropriate managers.
    AccumulatorComponent accumulatorComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::NONE));
    MassComponent massComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::NONE));
    MovementComponent movementComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::NONE));
    TransformComponent transformComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::NONE));

    // Register entity components with default managers.
    QueueAccumulatorComponentToRegister(accumulatorComponent);
    QueueMassComponentToRegister(massComponent);
    QueueMovementComponentToRegister(movementComponent);
    QueueTransformComponentToRegister(transformComponent);

    // Register entity with default systems.
    QueueableEntity earthPair(DomSim::Enumerations::SystemType::EARTH, entity);
    QueueEntityToRegister(earthPair);

    QueueableEntity integrationPair(DomSim::Enumerations::SystemType::INTEGRATION, entity);
    QueueEntityToRegister(integrationPair);

    return entity;
}


void EntityManager::CreateInertFSBoosterEntity(AccumulatorComponent &oldAcc, 
                                               MassComponent &oldMass,
                                               MovementComponent &oldMove,
                                               TransformComponent &oldTrans) {
    Entity entity{ nextId };
    ++nextId;

    // Create the new component id
    unsigned int newId = ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::FIRST_STAGE_SRM);

    AccumulatorComponent accumulatorComponent(oldAcc);
    accumulatorComponent.setId(newId);
    QueueAccumulatorComponentToRegister(accumulatorComponent);
    
    MassComponent massComponent(oldMass);
    massComponent.setId(newId);
    QueueMassComponentToRegister(massComponent);

    MovementComponent movementComponent(oldMove);
    movementComponent.setId(newId);
    QueueMovementComponentToRegister(movementComponent);

    TransformComponent transformComponent(oldTrans);
    transformComponent.setId(newId);
    QueueTransformComponentToRegister(transformComponent);

    // Register entity with default systems.
    QueueableEntity earthPair(DomSim::Enumerations::SystemType::EARTH, entity);
    QueueEntityToRegister(earthPair);

    QueueableEntity integrationPair(DomSim::Enumerations::SystemType::INTEGRATION, entity);
    QueueEntityToRegister(integrationPair);

}

void EntityManager::CreateInertSSBoosterEntity(AccumulatorComponent &oldAcc, 
                                               MassComponent &oldMass,
                                               MovementComponent &oldMove,
                                               TransformComponent &oldTrans) {
    Entity entity{ nextId };
    ++nextId;

    // Create the new component id
    unsigned int newId = ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::SECOND_STAGE_SRM);

    AccumulatorComponent accumulatorComponent(oldAcc);
    accumulatorComponent.setId(newId);
    QueueAccumulatorComponentToRegister(accumulatorComponent);
    
    MassComponent massComponent(oldMass);
    massComponent.setId(newId);
    QueueMassComponentToRegister(massComponent);

    MovementComponent movementComponent(oldMove);
    movementComponent.setId(newId);
    QueueMovementComponentToRegister(movementComponent);

    TransformComponent transformComponent(oldTrans);
    transformComponent.setId(newId);
    QueueTransformComponentToRegister(transformComponent);

    // Register entity with default systems.
    QueueableEntity earthPair(DomSim::Enumerations::SystemType::EARTH, entity);
    QueueEntityToRegister(earthPair);

    QueueableEntity integrationPair(DomSim::Enumerations::SystemType::INTEGRATION, entity);
    QueueEntityToRegister(integrationPair);

}

void EntityManager::QueueAccumulatorComponentToRegister(AccumulatorComponent &component)
{
    accumulatorComponentsToRegister[accumIndexTracker++] = component;
}

void EntityManager::QueueMassComponentToRegister(MassComponent &component)
{
    massComponentsToRegister[massIndexTracker++] = component;
}

void EntityManager::QueueMovementComponentToRegister(MovementComponent &component)
{
    movementComponentsToRegister[moveIndexTracker++] = component;
}

void EntityManager::QueueSSSRMComponentToRegister(SolidRocketMotorComponent& component) {
    ssSRMComponentsToRegister[ssSRMIndexTracker++] = component;
}


void EntityManager::QueueTransformComponentToRegister(TransformComponent &component)
{
    transformComponentsToRegister[transformIndexTracker++] = component;
}

void EntityManager::QueueEntityToRegister(QueueableEntity& pair)
{
    entitiesToRegister.emplace_back(pair);
}

uint16_t EntityManager::getNumQueuedEntities() { return entitiesToRegister.size(); }
void EntityManager::resetQueuedEntities() { entitiesToRegister.clear(); }
QueueableEntity& EntityManager::getQueuedEntity(uint16_t index) { return entitiesToRegister[index]; }

uint16_t EntityManager::getAccumIndexTracker() { return accumIndexTracker; }
void EntityManager::resetAccumIndexTracker() { accumIndexTracker = 0; }
AccumulatorComponent& EntityManager::getQueuedAccumulatorComponent(uint16_t index) { return accumulatorComponentsToRegister[index]; }

uint16_t EntityManager::getMassIndexTracker() { return massIndexTracker; }
void EntityManager::resetMassIndexTracker() { massIndexTracker = 0; }
MassComponent& EntityManager::getQueuedMassComponent(uint16_t index) { return massComponentsToRegister[index]; }

uint16_t EntityManager::getMovementIndexTracker() { return moveIndexTracker; }
void EntityManager::resetMovementIndexTracker() { moveIndexTracker = 0; }
MovementComponent& EntityManager::getQueuedMovementComponent(uint16_t index) { return movementComponentsToRegister[index]; }

uint16_t EntityManager::getTransformIndexTracker() { return transformIndexTracker; }
void EntityManager::resetTransformIndexTracker() { transformIndexTracker = 0; }
TransformComponent& EntityManager::getQueuedTransformComponent(uint16_t index) { return transformComponentsToRegister[index]; }

uint16_t EntityManager::getSSSRMIndexTracker() { return ssSRMIndexTracker; }
void EntityManager::resetSSSRMIndexTracker() { ssSRMIndexTracker = 0; }
SolidRocketMotorComponent& EntityManager::getQueuedSSSRMComponent(uint16_t index) { return ssSRMComponentsToRegister[index]; }


