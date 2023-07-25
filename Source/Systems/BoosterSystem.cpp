#include "BoosterSystem.h"

#include "../Components/Utilities.h"

BoosterSystem::BoosterSystem(BoosterType type, 
                  AccumulatorManager* accumulatorManager,
                  MassManager* massManager,
                  MovementManager* movementManager,
                  SolidRocketMotorManager* srmManager,
                  TransformManager* transformManager,
                  Simulation* simulation) : 
                  boosterType_(type),
                  accumulatorManager_(accumulatorManager),
                  massManager_(massManager),
                  movementManager_(movementManager),
                  srmManager_(srmManager),
                  transformManager_(transformManager),
                  simulation_(simulation) {}

void BoosterSystem::Update(real dt) {
    for (auto & entity : registeredEntities) {
        AccumulatorComponent& accComponent = accumulatorManager_->Lookup(entity);
        SolidRocketMotorComponent& srmComponent = srmManager_->Lookup(entity);
        MassComponent& massComponent = massManager_->Lookup(entity);

        Vector3 thrustVector = Vector3{1.0, 1.0, 1.0} * srmComponent.thrust;
        accComponent.forceAccumulator_eci += thrustVector;

        // Model the SRM burning its propellant mass.
        srmComponent.propellantMass -= 10.0;
        massComponent.mass -= 10.0;

        if (srmComponent.propellantMass <= 0.0) { 

            // Assume that right when the booster encounters burnout, it separates into its own entity.
            // This means:
            // 1) this booster system needs to stop tracking the SRM component,
            // 2) this booster system needs to unregister the entity associated with the SRM component.
            // 3) a new entity must be created for the burned out booster with the correct components
            // 4) the data in the new components must come from from the other components
            // 5) register the new entity and its components with the correct managers and systems.

            // 1) Stop tracking the SRM component.
            srmManager_->Destroy(entity); 

            // 2) Unregister the entity associated with the component
            entitiesToRemove.push_back(entity);

            // 3) Create a new entity that represents the inert, separated first stage booster with the correct components
            Entity newEntity = EntityManager::CreateEntity();

            // 4) New data comes from old data
            unsigned short newId;
            AccumulatorComponent &newAcc = accumulatorManager_->Lookup(newEntity);
            MassComponent &newMass = massManager_->Lookup(newEntity);
            MovementComponent &newMove = movementManager_->Lookup(newEntity);
            TransformComponent &newTrans = transformManager_->Lookup(newEntity);

            MovementComponent& movementComponent = movementManager_->Lookup(entity);
            TransformComponent& oldTrans = transformManager_->Lookup(entity);

            if (boosterType_ == FIRST_STAGE) { 
                newId = ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::FIRST_STAGE_SRM);

                // Create the new SRM component to track in the second stage booster system.
                SolidRocketMotorComponent newSrmComponent(ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::SECOND_STAGE_SRM));
                newSrmComponent.thrust = 100.0;
                newSrmComponent.inertMass = 400.0;
                newSrmComponent.propellantMass = 100.0;


                simulation_->RegisterEntity_SecondStageBoosterSystem(entity, newSrmComponent); 
            }
            else // Second Stage
            {
                newId = ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::SECOND_STAGE_SRM);
            }

            newAcc.forceAccumulator_eci = accComponent.forceAccumulator_eci;
            newAcc.torqueAccumulator_eci = accComponent.torqueAccumulator_eci;
            newAcc.setId(newId);

            newMass.mass = srmComponent.inertMass;
            newMass.setId(newId);

            newMove.velocity_eci = movementComponent.velocity_eci;
            newMove.acceleration_eci = movementComponent.acceleration_eci;
            newMove.setId(newId);

            newTrans.position_eci = oldTrans.position_eci;
            newTrans.setId(newId);

            // If this is a second stage booster system, all that will be left in the abstract missile component properties
            // are the properties that apply to the payload.
        }
    }

    UnregisterEntities();
}

void BoosterSystem::AddSrmComponent(Entity& entity, SolidRocketMotorComponent& srmComponent)
{
    srmManager_->Add(entity, srmComponent);
}

