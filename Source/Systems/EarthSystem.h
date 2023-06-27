#ifndef EARTH_SYSTEM_H
#define EARTH_SYSTEM_H

#include <iostream>

#include "System.h"

#include "../HelperMethods.h"

#include "../Components/AccumulatorComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/TransformComponent.h"

#include "../Core/TypeDefinitions.h"

#include "../Managers/AccumulatorManager.h"
#include "../Managers/MassManager.h"
#include "../Managers/MovementManager.h"
#include "../Managers/TransformManager.h"

#include "../MathTypes/Vector3.h"

class EarthSystem : public System
{
    public:

    EarthSystem(AccumulatorManager& accumulatorManager,
                MassManager& massManager,
                TransformManager& transformManager) : 
                accumulatorManager_(accumulatorManager),
                massManager_(massManager),
                transformManager_(transformManager) {};
    
    void Update(real dt) override {
        for (auto & entity : registeredEntities) {
            // Impart the forces produced by the Earth on entities here.
            // Rotational forces
            // Gravitational forces

            // Very basic gravity force.
            MassComponent& massComponent = massManager_.Lookup(entity);
            TransformComponent& transComponent = transformManager_.Lookup(entity);

            // Compute the force of gravity on the entity.
            real distance = HelperMethods::CalculateDistance(EARTH_POSITION, transComponent.position_eci);

            if (distance > 0.0)
            {
                real distance_squared = distance * distance;
                real gforce = (GRAVITATIONAL_CONSTANT * EARTH_MASS_KG * massComponent.mass) / distance_squared;

                // Calculate the direction of the force.
                Vector3 gforce_direction = transComponent.position_eci;
                gforce_direction.Normalize();
                gforce_direction *= -1 * gforce;
                accumulatorManager_.AddForceAtCG(entity, gforce_direction);
            }

        }
    }

    const Vector3 EARTH_POSITION{0.0, 0.0, 0.0};
    static constexpr real GRAVITATIONAL_CONSTANT = 0.0000000000667f;
    static constexpr real EARTH_MASS_KG = 5.972e+24f;

    private:

    AccumulatorManager& accumulatorManager_;
    MassManager& massManager_;
    TransformManager& transformManager_;

};
#endif //EARTH_SYSTEM_H