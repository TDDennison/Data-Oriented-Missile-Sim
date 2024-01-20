#ifndef SECOND_STAGE_BOOSTER_SYSTEM_H
#define SECOND_STAGE_BOOSTER_SYSTEM_H

#include <algorithm>
#include <iostream>

#include "System.h"

#include "MassComponent.h"
#include "MovementComponent.h"
#include "SolidRocketMotorComponent.h"
#include "TransformComponent.h"

#include "DomSimConstants.h"
#include "DomSimEnumerations.h"

#include "AttributesManager.h"
#include "TypeDefinitions.h"

#include "AccumulatorManager.h"
#include "EntityManager.h"
#include "ManagersConstants.h"
#include "MassManager.h"
#include "MovementManager.h"
#include "SolidRocketMotorManager.h"
#include "TransformManager.h"


class SecondStageBoosterSystem : public System
{
    public:

    SecondStageBoosterSystem(AccumulatorManager* accumulatorManager, 
                  MassManager* massManager,
                  MovementManager* movementManager,
                  SolidRocketMotorManager* srmManager,
                  TransformManager* transformManager) : 
                  accumulatorManager_(accumulatorManager),
                  massManager_(massManager),
                  movementManager_(movementManager),
                  srmManager_(srmManager),
                  transformManager_(transformManager){};
    
    virtual void Update(float dt, bool &allowMassDecrement) override;

    void AddSrmComponent(SolidRocketMotorComponent& srmComponent)
    {
        srmManager_->Add(srmComponent);
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

            attributesManager->AddAttribute<bool>("SS_TestBool", Core::Enumerations::AttributeType::BOOLEAN, Core::Constants::DEFAULT_BOOLEAN);
            attributesManager->AddAttribute<int>("SS_TestInt", Core::Enumerations::AttributeType::INT32, Core::Constants::DEFAULT_INT32);
        }
    };

    inline static const Attributes attributes{}; // Static constructor used to register attributes before main() is started.

    AccumulatorManager* accumulatorManager_;
    MassManager* massManager_;
    MovementManager* movementManager_;
    SolidRocketMotorManager* srmManager_;
    TransformManager* transformManager_;
};

#endif //SECOND_STAGE_BOOSTER_SYSTEM_H