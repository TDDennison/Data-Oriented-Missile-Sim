#include "SecondStageBoosterSystem.h"

#include "Utilities.h"
#include "Configurations.h"

void SecondStageBoosterSystem::Update(float dt, bool &allowMassDecrement) {
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
        Vector3 application_point_eci = transComponent.position_eci + DomSim::Constants::TVC_OFFSET_FROM_ORIGIN;
        Vector3 target_position_eci = Configurations::GetInstance()->GetTargetInterceptPoints()[0]; // Hard-coded to attack the first target.
        Vector3 vectorToTarget = Utilities::CalculateVectorBetweenPoints(transComponent.position_eci, target_position_eci); // Transform component should probably be cg position.
        vectorToTarget.Normalize();

        //std::cout << "Vector to target: " << vectorToTarget.x << " " << vectorToTarget.y << " " << vectorToTarget.z << std::endl;
        Vector3 thrustVector = vectorToTarget * srmComponent.thrust;
        //std::cout << "Thrust vector: " << thrustVector.x << " " << thrustVector.y << " " << thrustVector.z << std::endl;

        Vector3 position_cg_eci = transComponent.transformMatrix * massComponent.position_cg_body;
        accComponent.AddForceAtPoint(thrustVector, application_point_eci, position_cg_eci);

        // If the integration system is in the middle two frames of the RK4 method, no mass should be decremented.
        // This model needs to know about the integration system and/or which frame the integration system is in.
        // How can this be done in a data oriented fashion?
        // Probably has to be passed in, due to library dependency chain
        if (allowMassDecrement)
        {
            // Model the SRM burning its propellant mass.
            real massBurned = 0.1;
            srmComponent.propellantMass -= massBurned;
            massComponent.DecrementSubMass(massBurned, ComponentUtilities::ComponentDesignators::SECOND_STAGE_SRM);

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
                MassComponent newMass{};
                newMass.mass = srmComponent.inertMass;

                MovementComponent& movementComponent = movementManager_->Lookup(entity);

                EntityManager::GetInstance()->CreateInertSSBoosterEntity(accComponent, newMass, movementComponent, transComponent);
                std::cout << "Created new inert second stage entity" << std::endl;

                // Finally, remove the first stage submass
                massComponent.RemoveSubmass(ComponentUtilities::ComponentDesignators::SECOND_STAGE_SRM);

                // If this is a second stage booster system, all that will be left in the abstract missile component properties
                // are the properties that apply to the payload.
            }
        }
    }

    UnregisterEntities();
}

