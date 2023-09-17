#ifndef EARTH_SYSTEM_H
#define EARTH_SYSTEM_H

#include <iostream>

#include "System.h"

#include "../HelperMethods.h"

#include "../Components/AccumulatorComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/TransformComponent.h"

#include "../Core/AttributesManager.h"
#include "../Core/TypeDefinitions.h"

#include "../Managers/AccumulatorManager.h"
#include "../Managers/MassManager.h"
#include "../Managers/MovementManager.h"
#include "../Managers/TransformManager.h"

#include "../MathTypes/Vector3.h"

class EarthSystem : public System
{
    public:
    inline static EarthSystem* GetInstance() {
        if(instance == nullptr) { instance = new EarthSystem(*AccumulatorManager::GetInstance(), *MassManager::GetInstance(), *TransformManager::GetInstance()); }
        return instance;
    }

    void Initialize() override {
        // Grab the necessary attribtues.
        AttributesManager *attributesManager = AttributesManager::GetInstance();

        executionOrder_ = attributesManager->GetAttribute<uint16_t>(Constants::EXECUTION_ORDER_EARTH_SYSTEM);

        std::cout << "Earth system execution order is: " << executionOrder_ << std::endl;
    }
    
    void Update(float dt) override {

        return;
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

    EarthSystem(AccumulatorManager& accumulatorManager,
                MassManager& massManager,
                TransformManager& transformManager) : 
                accumulatorManager_(accumulatorManager),
                massManager_(massManager),
                transformManager_(transformManager),
                System() {};
    inline static EarthSystem* instance = nullptr;

    // Private class used to register attributes prior to runtime starting.
    // This is done through the use of static construction of this class.
    class Attributes
    {
        public:
        Attributes()
        {
            std::cout << "Earth System adding attributes." << std::endl;
            AttributesManager *attributesManager = AttributesManager::GetInstance();

            attributesManager->AddAttribute<uint16_t>(Constants::EXECUTION_ORDER_EARTH_SYSTEM, AttributeType::UINT16, Constants::DEFAULT_UINT16);
        }
    };

    inline static const Attributes attributes{}; // Static constructor used to register attributes before main() is started.

    AccumulatorManager& accumulatorManager_;
    MassManager& massManager_;
    TransformManager& transformManager_;
};
#endif //EARTH_SYSTEM_H