#ifndef SYSTEM_H
#define SYSTEM_H

#include <bitset>
#include <iostream>
#include <vector>

#include "DomSimConstants.h"
#include "Entity.h"

#include "TypeDefinitions.h"

class System {
public:
  System();
  
  // Initialize the System — This happens *before* the game starts but *after* the world has been registered.
  virtual void Initialize();

  // Called every game update
  virtual void Update(float dt);
  virtual void Update(float dt, float &dtOut);
  
  // This entity fits our current requirements
  virtual void RegisterEntity(Entity entity);
  
  // This entity has stopped fitting our current requirements
  void UnregisterEntity(Entity entity);

  // Unregister all entities that are no longer needed.
  void UnregisterEntities();

  // Compares two intervals according to starting times.
  static bool compareExecutionOrder(System *s1, System *s2);

  uint16_t executionOrder_ = DomSim::Constants::DEFAULT_UINT16;

protected:
  // Specifies which components our system cares about — its size should = the number of different components
  std::bitset<32> systemSignature{};

  // These entities fit the systemSignature and should be iterated upon for any functionality
  std::vector<Entity> registeredEntities{};

  std::vector<Entity> entitiesToRemove{};
};

#endif //SYSTEM_H