#include "IntegrationSystem_Euler.h"

IntegrationSystem_Euler::IntegrationSystem_Euler(AccumulatorManager* accumulatorManager,
                        MassManager* massManager,
                        MovementManager* movementManager,
                        TransformManager* transformManager) : 
                        accumulatorManager_(accumulatorManager),
                        massManager_(massManager),
                        movementManager_(movementManager),
                        transformManager_(transformManager) {
                        }

void IntegrationSystem_Euler::Update(float dt, float &dtOut, bool &shouldLog, bool &allowMassDecrement) {
    dtOut = dt; // Euler integration is a single pass.
    
    // Log every frame with Euler integration.
    shouldLog = true;

    // Mass decrementing is allowed for every frame in Euler integration.
    allowMassDecrement = true;

    for (auto & entity : registeredEntities) {
        AccumulatorComponent& accumulatorComponent = accumulatorManager_->Lookup(entity);
        TransformComponent& transform = transformManager_->Lookup(entity);
        MassComponent& massComponent = massManager_->Lookup(entity);
        MovementComponent& movement = movementManager_->Lookup(entity);

        // Update the linear properties.
        // ============================================================
        Vector3 lastFrameAcceleration = movement.acceleration_eci;
        real inverseMass = 1.0 / massComponent.mass;
        movement.acceleration_eci.AddScaledVector(accumulatorComponent.forceAccumulator_eci, inverseMass);

        // Update the linear position and velocity. Need to update the missile frame position, and missile cg by the same amount.
        transform.position_eci.AddScaledVector(movement.velocity_eci, dt);
        movement.velocity_eci.AddScaledVector(lastFrameAcceleration, dt); // Update velocity to new value only after position has used the old values.


        // Update the rotational properties.
        // ============================================================
        Vector3 lastFrameAngAcceleration = movement.angular_acceleration_eci;

        // Convert the inertia tensor from the body frame to the ECI frame.
        Matrix3 rotationMatrix;
        rotationMatrix.SetOrientation(transform.orientation_eci);
        Matrix3 inverseInertiaTensor_eci = rotationMatrix.Inverse() * massComponent.inertiaTensor.Inverse();
        movement.angular_acceleration_eci.AddScaledVector(inverseInertiaTensor_eci * accumulatorComponent.torqueAccumulator_eci, dt);

        // Update the angular position and velocity.
        movement.angular_velocity_eci.AddScaledVector(lastFrameAngAcceleration, dt); // Update velocity to new value only after orientation has used the old value.

        //transform.orientation_eci.RotateByVector(movement.angular_velocity_eci * dt);
        transform.orientation_eci.AddScaledVector(movement.angular_velocity_eci, dt);

        // Update the derived data.
        transform.transformMatrix.SetOrientationAndPosition(transform.orientation_eci, transform.position_eci);
    }

    // Clear the accumulators.
    accumulatorManager_->ClearAccumulators();
}
