#include "IntegrationSystem_RK4.h"

IntegrationSystem_RK4::IntegrationSystem_RK4(AccumulatorManager* accumulatorManager,
                        MassManager* massManager,
                        MovementManager* movementManager,
                        TransformManager* transformManager) : 
                        accumulatorManager_(accumulatorManager),
                        massManager_(massManager),
                        movementManager_(movementManager),
                        transformManager_(transformManager) {}

void IntegrationSystem_RK4::RegisterEntity(Entity entity) {
    System::RegisterEntity(entity);
    TransformComponent& transformComponent = transformManager_->Lookup(entity);
    MovementComponent& movementComponent = movementManager_->Lookup(entity);
    AccumulatorComponent& accumulatorComponent = accumulatorManager_->Lookup(entity);

    // We are attempting to calculate k1, before doing so we need to save the y_0 states.
    // Add the state to the store objects based on its entity id.
    entityToRk4Store[entity.id] = storeIndexTracker;
    transformComponentStore[storeIndexTracker][0] = transformComponent;
    movementComponentStore[storeIndexTracker][0] = movementComponent;

    ++storeIndexTracker; // Increment the tracker

    // After y_0 states have been saved the initial conditions can be run through the 
    // simulation.
}

void IntegrationSystem_RK4::Update(float dt, float &dtOut, bool &shouldLog, bool& allowMassDecrement){

    dtOut = dt; // In case there ar no registered entities

    for (auto & entity : registeredEntities) {
        AccumulatorComponent& accumulatorComponent = accumulatorManager_->Lookup(entity);
        MassComponent& massComponent = massManager_->Lookup(entity);
        TransformComponent& transformComponent = transformManager_->Lookup(entity);
        MovementComponent& movementComponent = movementManager_->Lookup(entity);

        // We are only integrating the position, velocity and acceleration properties here.

        if(kpass == 1)
        {
            // Mass decrementing is allowed on the first and last frames of Rk4
            allowMassDecrement = true;

            // Log the very first frame.
            shouldLog = true;

            // Now k1 has been calculated by running t_n and y_n conditions through the simulation.
            // Need to save k1 states for later.
            unsigned int storeIndex = entityToRk4Store[entity.id];
            transformComponentStore[storeIndex][1] = transformComponent;
            movementComponentStore[storeIndex][1] = movementComponent;

            // Update the dtOut to be half of the original dt
            dtOut = dt * 0.5;

            // Update the conditions to be of the form needed to calculate k2.
            // ============================================================

            // Update the linear position and velocity.
            // get x_0
            Vector3 &pos_0 = transformComponentStore[storeIndex][0].position_eci;
            Vector3 &vel_0 = movementComponentStore[storeIndex][0].velocity_eci;

            transformComponent.position_eci = (movementComponent.velocity_eci * dtOut) + pos_0;
            movementComponent.velocity_eci = (movementComponent.acceleration_eci * dtOut) + vel_0;

            // Update the acceleration.
            real inverseMass = 1.0 / massComponent.mass;
            movementComponent.acceleration_eci.AddScaledVector(accumulatorComponent.forceAccumulator_eci, inverseMass);

            // Now the data is ready to compute k2.
            continue;
        }

        if(kpass == 2)
        {
            // Mass decrementing is only allowed on the first and last frames of Rk4
            allowMassDecrement = false;

            // Don't log the middle frames.
            shouldLog = false;

            // Now k2 has been calculated by running t_n + dt/2 and y_n + dt/2
            // Need to save k2 states for later.
            unsigned int storeIndex = entityToRk4Store[entity.id];
            transformComponentStore[storeIndex][2] = transformComponent;
            movementComponentStore[storeIndex][2] = movementComponent;

            dtOut = 0.0;

            // Update the conditions to be of the form needed to calculate k2.
            // ============================================================
            // Update the linear position and velocity.
            // get x_0
            Vector3 &pos_0 = transformComponentStore[storeIndex][0].position_eci;
            Vector3 &vel_0 = movementComponentStore[storeIndex][0].velocity_eci;

            transformComponent.position_eci = (movementComponent.velocity_eci * dt * 0.5) + pos_0;
            movementComponent.velocity_eci = (movementComponent.acceleration_eci * dt * 0.5) + vel_0;

            // Update the acceleration.
            real inverseMass = 1.0 / massComponent.mass;
            movementComponent.acceleration_eci.AddScaledVector(accumulatorComponent.forceAccumulator_eci, inverseMass);

            continue;
        }

        if(kpass == 3)
        {
            // Mass decrementing is only allowed on the first and last frames of Rk4
            allowMassDecrement = false;

            // Don't log the middle frames.
            shouldLog = false;

            // Now k3 has been calculated by running t_n + dt/2 and y_n + dt/2
            // Need to save k3 states for later.
            unsigned int storeIndex = entityToRk4Store[entity.id];
            transformComponentStore[storeIndex][3] = transformComponent;
            movementComponentStore[storeIndex][3] = movementComponent;

            // Update the dtOut to be zero, need to run the same point in time
            dtOut = dt * 0.5;

            // Update the linear position and velocity.
            // get x_0
            Vector3 &pos_0 = transformComponentStore[storeIndex][0].position_eci;
            Vector3 &vel_0 = movementComponentStore[storeIndex][0].velocity_eci;

            transformComponent.position_eci = (movementComponent.velocity_eci * dt * 0.5) + pos_0;
            movementComponent.velocity_eci = (movementComponent.acceleration_eci * dt * 0.5) + vel_0;

            // Update the acceleration.
            real inverseMass = 1.0 / massComponent.mass;
            movementComponent.acceleration_eci.AddScaledVector(accumulatorComponent.forceAccumulator_eci, inverseMass);

            continue;
        }

        if(kpass == 4)
        {
            // Mass decrementing is only allowed on the first and last frames of Rk4
            allowMassDecrement = true;

            // Log the last RK4 frame, i.e. the full timestep.
            shouldLog = true;

            // Now k4 has been calculated by running t_n + dt/2 and y_n + dt/2
            // Need to save k4 states for later.
            unsigned int storeIndex = entityToRk4Store[entity.id];
            transformComponentStore[storeIndex][4] = transformComponent;
            movementComponentStore[storeIndex][4] = movementComponent;

            // Get the data needed to compute the integrated values.
            transformComponent.position_eci = transformComponentStore[storeIndex][0].position_eci + 
                                                (movementComponentStore[storeIndex][1].velocity_eci + 
                                                movementComponentStore[storeIndex][2].velocity_eci * 2 + 
                                                movementComponentStore[storeIndex][3].velocity_eci * 2 + 
                                                movementComponentStore[storeIndex][4].velocity_eci) * (dt / 6);

            movementComponent.velocity_eci = movementComponentStore[storeIndex][0].velocity_eci + 
                                                (movementComponentStore[storeIndex][1].acceleration_eci + 
                                                movementComponentStore[storeIndex][2].acceleration_eci * 2 + 
                                                movementComponentStore[storeIndex][3].acceleration_eci * 2 + 
                                                movementComponentStore[storeIndex][4].acceleration_eci) * (dt / 6);

            // Update the acceleration.
            real inverseMass = 1.0 / massComponent.mass;
            movementComponent.acceleration_eci.AddScaledVector(accumulatorComponent.forceAccumulator_eci, inverseMass);

            // Update the dtOut to be half of the original dt, because the current time is already t_n + dt / 2.
            // adding another dt / 2 will bring us to the full dt.
            dtOut = dt * 0.5;

            continue;
        }
    }

    // Reset the integration system.
    if (kpass == 4)
    {
        storeIndexTracker = 0;

        for (auto & entity : registeredEntities) {
            AccumulatorComponent& accumulatorComponent = accumulatorManager_->Lookup(entity);
            TransformComponent& transformComponent = transformManager_->Lookup(entity);
            MassComponent& massComponent = massManager_->Lookup(entity);
            MovementComponent& movementComponent = movementManager_->Lookup(entity);

            // We are attempting to calculate k2, before doing so we need to save the y_0 states.
            // Add the state to the store objects based on its entity id.
            entityToRk4Store[entity.id] = storeIndexTracker;
            transformComponentStore[storeIndexTracker][0] = transformComponent;
            movementComponentStore[storeIndexTracker][0] = movementComponent;

            // The same data is set into the k1 stores because the derivatives have been 
            // calculated in the same frame.
            // i.e velocity has been calculated and will be used for k1 of position.
            transformComponentStore[storeIndexTracker][1] = transformComponent;
            movementComponentStore[storeIndexTracker][1] = movementComponent;

            ++storeIndexTracker; // Increment the tracker

            // After y_0 states have been saved the initial conditions can be run through the 
            // simulation.
        }
    }

    // Clear the accumulators.
    accumulatorManager_->ClearAccumulators();

    // Reset to kpass = 2 because pass 4 can be reused for pass 1 of the next frame.
    kpass = ++kpass > 4 ? 2 : kpass;
}
