#ifndef INTEGRATION_SYSTEM_RK4
#define INTEGRATION_SYSTEM_RK4

#include <iostream>

#include "TransformComponent.h"
#include "MovementComponent.h"

#include "TypeDefinitions.h"

#include "ManagersConstants.h"
#include "AccumulatorManager.h"
#include "MovementManager.h"
#include "TransformManager.h"

#include "IIntegrationSystem.h"

class IntegrationSystem_RK4 : public IIntegrationSystem {

  public:

  IntegrationSystem_RK4(AccumulatorManager* accumulatorManager,
                          MassManager* massManager,
                          MovementManager* movementManager,
                          TransformManager* transformManager);

  void RegisterEntity(Entity entity) override;

  void Update(float dt, float &dtOut, bool &shouldLog) override;
  
  void Update(float dt, float &dtOut) override;

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
  TransformComponent transformComponentStore[Managers::Constants::MaxComponents][5]{};
  MovementComponent movementComponentStore[Managers::Constants::MaxComponents][5]{};

};

#endif // INTEGRATION_SYSTEM_RK4