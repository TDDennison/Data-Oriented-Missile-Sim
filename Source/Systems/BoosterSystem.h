#ifndef BOOSTER_SYSTEM_H
#define BOOSTER_SYSTEM_H

#include <algorithm>
#include <iostream>

#include "System.h"

#include "../Components/MassComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SolidRocketMotorComponent.h"
#include "../Components/TransformComponent.h"

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

    BoosterType boosterType_;
    AccumulatorManager* accumulatorManager_;
    MassManager* massManager_;
    MovementManager* movementManager_;
    SolidRocketMotorManager* srmManager_;
    TransformManager* transformManager_;
    Simulation* simulation_;

};

#endif //BOOSTER_SYSTEM_H