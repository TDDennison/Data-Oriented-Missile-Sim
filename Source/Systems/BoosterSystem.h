#ifndef BOOSTER_SYSTEM_H
#define BOOSTER_SYSTEM_H

#include <algorithm>
#include <iostream>

#include "System.h"

#include "../Components/MassComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SolidRocketMotorComponent.h"
#include "../Components/TransformComponent.h"

#include "../Constants.h"

#include "../Core/AttributesManager.h"
#include "../Core/TypeDefinitions.h"

#include "../Managers/AccumulatorManager.h"
#include "../Managers/EntityManager.h"
#include "../Managers/Managers.h"
#include "../Managers/MassManager.h"
#include "../Managers/MovementManager.h"
#include "../Managers/SolidRocketMotorManager.h"
#include "../Managers/TransformManager.h"

#include "../Simulation.h"

class Simulation;

class BoosterSystem : public System
{
    public:

    BoosterSystem(BoosterType type,
                  AccumulatorManager* accumulatorManager, 
                  MassManager* massManager,
                  MovementManager* movementManager,
                  SolidRocketMotorManager* srmManager,
                  TransformManager* transformManager,
                  Simulation* simulation);
    
    void Update(real dt) override;

    void AddSrmComponent(Entity& entity, SolidRocketMotorComponent& SrmComponent);

    private:

    // Private class used to register attributes prior to runtime starting.
    // This is done through the use of static construction of this class.
    class Attributes
    {
        public:
        Attributes()
        {
            std::cout << "Booster System adding attributes." << std::endl;
            AttributesManager *attributesManager = AttributesManager::GetInstance();

            attributesManager->AddAttribute<bool>("TestBool", AttributeType::BOOLEAN, Constants::DEFAULT_BOOLEAN);
            attributesManager->AddAttribute<int>("TestInt", AttributeType::INT32, Constants::DEFAULT_INT32);
        }
    };

    inline static const Attributes attributes{}; // Static constructor used to register attributes before main() is started.

    BoosterType boosterType_;
    AccumulatorManager* accumulatorManager_;
    MassManager* massManager_;
    MovementManager* movementManager_;
    SolidRocketMotorManager* srmManager_;
    TransformManager* transformManager_;
    Simulation* simulation_;

};

#endif //BOOSTER_SYSTEM_H