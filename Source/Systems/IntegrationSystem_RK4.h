#ifndef INTEGRATION_SYSTEM_RK4
#define INTEGRATION_SYSTEM_RK4

#include <iostream>

#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"

#include "../Core/TypeDefinitions.h"

#include "../Managers/Managers.h"
#include "../Managers/AccumulatorManager.h"
#include "../Managers/MovementManager.h"
#include "../Managers/TransformManager.h"

#include "System.h"

class IntegrationSystem_RK4 : public System {

  public:

  IntegrationSystem_RK4(AccumulatorManager* accumulatorManager,
                          MassManager* massManager,
                          MovementManager* movementManager,
                          TransformManager* transformManager) : 
                          accumulatorManager_(accumulatorManager),
                          massManager_(massManager),
                          movementManager_(movementManager),
                          transformManager_(transformManager) {}

    void RegisterEntity(Entity entity) override {
        System::RegisterEntity(entity);
        TransformComponent& transformComponent = transformManager_->Lookup(entity);
        MovementComponent& movementComponent = movementManager_->Lookup(entity);

        AccumulatorComponent& accumulatorComponent = accumulatorManager_->Lookup(entity);

        // We are attempting to calculate k1, before doing so we need to save the y_0 states.
        // Add the state to the store objects based on its entity id.
        entityToRk4Store[entity.id] = storeIndexTracker;
        transformComponentStore[storeIndexTracker][0] = transformComponent;
        movementComponentStore[storeIndexTracker][0] = movementComponent;
        forceComponentStore[storeIndexTracker] = accumulatorComponent.forceAccumulator_eci;

        ++storeIndexTracker; // Increment the tracker

        // After y_0 states have been saved the initial conditions can be run through the 
        // simulation.
    }
  
  void Update(real dt, real &dtOut) override {

    dtOut = dt; // In case there arr no register entities

    for (auto & entity : registeredEntities) {
      TransformComponent& transformComponent = transformManager_->Lookup(entity);
      MovementComponent& movementComponent = movementManager_->Lookup(entity);

      // We are only integrating the position, velocity and acceleration properties here.

      if(kpass == 1)
      {
        // Now k1 has been calculated by running t_n and y_n conditions through the simulation.
        // Need to save k1 states for later.
        unsigned int storeIndex = entityToRk4Store[entity.id] = storeIndexTracker;
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

        transformComponent.position_eci = (transformComponent.position_eci * dtOut) + pos_0;
        movementComponent.velocity_eci = (movementComponent.velocity_eci * dtOut) + vel_0;

        // Now the data is ready to compute k2.
        continue;
      }

      if(kpass == 2)
      {
        // Now k2 has been calculated by running t_n + dt/2 and y_n + dt/2
        // Need to save k2 states for later.
        unsigned int storeIndex = entityToRk4Store[entity.id] = storeIndexTracker;
        transformComponentStore[storeIndex][2] = transformComponent;
        movementComponentStore[storeIndex][2] = movementComponent;

        dtOut = dt * 0.5;

        // Update the conditions to be of the form needed to calculate k2.
        // ============================================================

        // Update the linear position and velocity.
        // get x_0
        Vector3 &pos_0 = transformComponentStore[storeIndex][0].position_eci;
        Vector3 &vel_0 = movementComponentStore[storeIndex][0].velocity_eci;

        transformComponent.position_eci = (transformComponent.position_eci * dtOut) + pos_0;
        movementComponent.velocity_eci = (movementComponent.velocity_eci * dtOut) + vel_0;
      }

      if(kpass == 3)
      {
        // Now k3 has been calculated by running t_n + dt/2 and y_n + dt/2
        // Need to save k3 states for later.
        unsigned int storeIndex = entityToRk4Store[entity.id] = storeIndexTracker;
        transformComponentStore[storeIndex][3] = transformComponent;
        movementComponentStore[storeIndex][3] = movementComponent;

        // Update the dtOut to be zero, need to run the same point in time
        dtOut = 0;

        // Update the linear position and velocity.
        // get x_0
        Vector3 &pos_0 = transformComponentStore[storeIndex][0].position_eci;
        Vector3 &vel_0 = movementComponentStore[storeIndex][0].velocity_eci;

        transformComponent.position_eci = (transformComponent.position_eci * dt * 0.5) + pos_0;
        movementComponent.velocity_eci = (movementComponent.velocity_eci * dt * 0.5) + vel_0;
      }

      if(kpass == 4)
      {
        MassComponent& massComponent = massManager_->Lookup(entity);

        // Now k4 has been calculated by running t_n + dt/2 and y_n + dt/2
        // Need to save k4 states for later.
        unsigned int storeIndex = entityToRk4Store[entity.id] = storeIndexTracker;
        transformComponentStore[storeIndex][4] = transformComponent;
        movementComponentStore[storeIndex][4] = movementComponent;

        // Get the data needed to compute the integrated values.
        transformComponent.position_eci = transformComponentStore[storeIndex][0].position_eci + 
                                          (transformComponentStore[storeIndex][1].position_eci + 
                                           transformComponentStore[storeIndex][2].position_eci * 2 + 
                                           transformComponentStore[storeIndex][3].position_eci * 2 + 
                                           transformComponentStore[storeIndex][4].position_eci) * (dt / 6);

        movementComponent.velocity_eci = movementComponentStore[storeIndex][0].velocity_eci + 
                                          (movementComponentStore[storeIndex][1].velocity_eci + 
                                           movementComponentStore[storeIndex][2].velocity_eci * 2+ 
                                           movementComponentStore[storeIndex][3].velocity_eci * 2 + 
                                           movementComponentStore[storeIndex][4].velocity_eci) * (dt / 6);

        // Update the dtOut to be half of the original dt, because the current time is already t_n + dt / 2.
        // adding another dt / 2 will bring us to the full dt.
        dtOut = dt * 0.5;

        // Compute the final values for the RK4 integration.
        // Acceleration forces are assumed to be constant over the full dt timestep.
        real inverseMass = 1.0 / massComponent.mass;
        movementComponent.acceleration_eci.AddScaledVector(forceComponentStore[storeIndex], inverseMass);
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

                // We are attempting to calculate k1, before doing so we need to save the y_0 states.
                // Add the state to the store objects based on its entity id.
                entityToRk4Store[entity.id] = storeIndexTracker;
                transformComponentStore[storeIndexTracker][0] = transformComponent;
                movementComponentStore[storeIndexTracker][0] = movementComponent;
                forceComponentStore[storeIndexTracker] = accumulatorComponent.forceAccumulator_eci;

                ++storeIndexTracker; // Increment the tracker

                // After y_0 states have been saved the initial conditions can be run through the 
                // simulation.
        }
    }

    // Clear the accumulators.
    accumulatorManager_->ClearAccumulators();
    kpass = ++kpass > 4 ? 1 : kpass;
  }

  private:

  AccumulatorManager* accumulatorManager_;
  TransformManager* transformManager_;
  MassManager* massManager_;
  MovementManager* movementManager_;

  // y_n+1 = y_n + h/6(k1 + 2k2 + 2k3+ k4)
  // t_n+t = t_n + h
  // k1 = f(t_n, y_n) 
  // k2 = f(t_n + h/2, y_n + h*k1/2)
  // k3 = f(t_n + h/2, y_n + h*k2/2)
  // k4 = f(t_n + h, y_n + h*k3)
  unsigned int kpass = 1;
  unsigned int storeIndexTracker = 0;
  std::map<unsigned int, unsigned int> entityToRk4Store{};

  // 5 indexes per component.
  // Index 0: y_n (the original value for time t_n)
  // Index 1: k1
  // Index 2: k2
  // Index 3: k3
  // Index 4: k4
  Vector3 forceComponentStore[MaxComponents];
  TransformComponent transformComponentStore[MaxComponents][5]{};
  MovementComponent movementComponentStore[MaxComponents][5]{};

};

#endif // INTEGRATION_SYSTEM_RK4