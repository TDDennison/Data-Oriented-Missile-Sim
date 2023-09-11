#ifndef FIRST_STAGE_BOOSTER_SYSTEM_H
#define FIRST_STAGE_BOOSTER_SYSTEM_H

#include <algorithm>
#include <iostream>

#include "../System.h"

#include "../../Components/MassComponent.h"
#include "../../Components/MovementComponent.h"
#include "../../Components/SolidRocketMotorComponent.h"
#include "../../Components/TransformComponent.h"

#include "../../Constants.h"

#include "../../Core/AttributesManager.h"
#include "../../Core/TypeDefinitions.h"

#include "../../Managers/AccumulatorManager.h"
#include "../../Managers/EntityManager.h"
#include "../../Managers/Managers.h"
#include "../../Managers/MassManager.h"
#include "../../Managers/MovementManager.h"
#include "../../Managers/SolidRocketMotorManager.h"
#include "../../Managers/TransformManager.h"

#include "../../Simulation.h"

class Simulation;

class FirstStageBoosterSystem : public System
{
    public:

    FirstStageBoosterSystem(AccumulatorManager* accumulatorManager, 
                  MassManager* massManager,
                  MovementManager* movementManager,
                  SolidRocketMotorManager* srmManager,
                  TransformManager* transformManager,
                  Simulation* simulation) : 
                  accumulatorManager_(accumulatorManager),
                  massManager_(massManager),
                  movementManager_(movementManager),
                  srmManager_(srmManager),
                  transformManager_(transformManager),
                  simulation_(simulation){};
    
    void Update(real dt) override;

    void AddSrmComponent(Entity& entity, SolidRocketMotorComponent& srmComponent)
    {
        srmManager_->Add(entity, srmComponent);
    }

    protected:

    // Private class used to register attributes prior to runtime starting.
    // This is done through the use of static construction of this class.
    class Attributes
    {
        public:
        Attributes()
        {
            std::cout << "Booster System adding attributes." << std::endl;
            AttributesManager *attributesManager = AttributesManager::GetInstance();

            attributesManager->AddAttribute<bool>("FS_TestBool", AttributeType::BOOLEAN, Constants::DEFAULT_BOOLEAN);
            attributesManager->AddAttribute<int>("FS_TestInt", AttributeType::INT32, Constants::DEFAULT_INT32);
        }
    };

    inline static const Attributes attributes{}; // Static constructor used to register attributes before main() is started.

    AccumulatorManager* accumulatorManager_;
    MassManager* massManager_;
    MovementManager* movementManager_;
    SolidRocketMotorManager* srmManager_;
    TransformManager* transformManager_;
    Simulation* simulation_;

};

#endif //FIRST_STAGE_BOOSTER_SYSTEM_H