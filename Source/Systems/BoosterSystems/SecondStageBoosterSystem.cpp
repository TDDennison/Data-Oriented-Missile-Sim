#include "SecondStageBoosterSystem.h"

#include "../../Components/Utilities.h"
#include "../../Core/Configurations.h"

void SecondStageBoosterSystem::Update(float dt) {
    for (auto & entity : registeredEntities) {
        AccumulatorComponent& accComponent = accumulatorManager_->Lookup(entity);
        SolidRocketMotorComponent& srmComponent = srmManager_->Lookup(entity);
        MassComponent& massComponent = massManager_->Lookup(entity);
        TransformComponent& transComponent = transformManager_->Lookup(entity);


        //================================================================================ 
        // VERY BASIC TVC SYSTEM, IT ALWAYS POINTS TOWARD THE TARGET TRUTH 
        //================================================================================ 
        // Compute the thrust vector based on the application point of the TVC.
        // 1) Find the application point in ECI
        // 2) Compute the thrust vector in ECI (The vector from the CG of the missile to the target)
        Vector3 application_point_eci = transComponent.position_eci + Constants::TVC_OFFSET_FROM_ORIGIN;
        Vector3 target_position_eci = Configurations::GetInstance()->GetTargetInterceptPoints()[0]; // Hard-coded to attack the first target.
        Vector3 vectorToTarget = HelperMethods::CalculateVectorBetweenPoints(transComponent.position_eci, target_position_eci); // Transform component should probably be cg position.
        vectorToTarget.Normalize();

        //std::cout << "Vector to target: " << vectorToTarget.x << " " << vectorToTarget.y << " " << vectorToTarget.z << std::endl;
        Vector3 thrustVector = vectorToTarget * srmComponent.thrust;
        //std::cout << "Thrust vector: " << thrustVector.x << " " << thrustVector.y << " " << thrustVector.z << std::endl;

        Vector3 position_cg_eci = transComponent.transformMatrix * massComponent.position_cg_body;
        accComponent.AddForceAtPoint(thrustVector, application_point_eci, position_cg_eci);

        // Model the SRM burning its propellant mass.
        srmComponent.propellantMass -= 0.01;
        massComponent.DecrementSubMass(0.1, ComponentUtilities::ComponentDesignators::SECOND_STAGE_SRM);

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

            std::cout << "Created new second stage entity" << std::endl;
            newId = ComponentUtilities::CreateComponentId(entity.id, ComponentUtilities::SECOND_STAGE_SRM);

            newAcc.forceAccumulator_eci = accComponent.forceAccumulator_eci;
            newAcc.torqueAccumulator_eci = accComponent.torqueAccumulator_eci;
            newAcc.setId(newId);

            newMass.mass = srmComponent.inertMass;
            newMass.setId(newId);

            newMove.velocity_eci = movementComponent.velocity_eci;
            newMove.acceleration_eci = movementComponent.acceleration_eci;
            newMove.setId(newId);

            newTrans.position_eci = transComponent.position_eci;
            newTrans.setId(newId);

            // If this is a second stage booster system, all that will be left in the abstract missile component properties
            // are the properties that apply to the payload.
        }
    }

    UnregisterEntities();
}

