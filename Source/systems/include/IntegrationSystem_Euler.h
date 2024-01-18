#ifndef MOTION_SYSTEM_H
#define MOTION_SYSTEM_H

#include <iostream>

#include "TransformComponent.h"
#include "MovementComponent.h"

#include "TypeDefinitions.h"

#include "ManagersConstants.h"
#include "AccumulatorManager.h"
#include "MovementManager.h"
#include "TransformManager.h"

#include "IIntegrationSystem.h"

class IntegrationSystem_Euler : public IIntegrationSystem {

  public:

  IntegrationSystem_Euler(AccumulatorManager* accumulatorManager,
                          MassManager* massManager,
                          MovementManager* movementManager,
                          TransformManager* transformManager);

  void Update(float dt, float &dtOut, bool &shouldLog);
  
  void Update(float dt, float &dtOut) override;

  private:

  AccumulatorManager* accumulatorManager_;
  TransformManager* transformManager_;
  MassManager* massManager_;
  MovementManager* movementManager_;
};

#endif //MOTION_SYSTEM_H