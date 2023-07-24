#ifndef SYSTEM_H
#define SYSTEM_H

#include <bitset>
#include <iostream>
#include <vector>

#include "../Entity.h"

#include "../Core/TypeDefinitions.h"

class System {
public:
  System() {}
  
  // Initialize the System — This happens *before* the game starts but *after* the world has been registered.
  virtual void Initialize() {};

  // Called every game update
  virtual void Update(real dt) {};
  
  // This entity fits our current requirements
  void RegisterEntity(Entity entity) {
    registeredEntities.push_back(entity);
  }
  
  // This entity has stopped fitting our current requirements
  void UnregisterEntity(Entity entity) {
    for (auto it = registeredEntities.begin(); it != registeredEntities.end(); ++it) {
      Entity e = *it;
      if (e.id == entity.id) {
        registeredEntities.erase(it);
        return;
      }
    }
  }

  // Unregister all entities that are no longer needed.
  void UnregisterEntities()
  {
    for (auto entity : entitiesToRemove)
    {
      std::cout << "Attempting to remove entity from system: " << entity.id << std::endl;
      auto it = std::find(registeredEntities.begin(), registeredEntities.end(), entity);

      if (it != registeredEntities.end()) {
        // swap the one to be removed with the last element
        // and remove the item at the end of the container
        // to prevent moving all items after entity by one
        std::swap(*it, registeredEntities.back());
        registeredEntities.pop_back();
      }
    }

    entitiesToRemove.clear();
  }

  uint16_t executionOrder_ = Constants::DEFAULT_UINT16;

protected:
  // Specifies which components our system cares about — its size should = the number of different components
  std::bitset<32> systemSignature{};

  // These entities fit the systemSignature and should be iterated upon for any functionality
  std::vector<Entity> registeredEntities{};

  std::vector<Entity> entitiesToRemove{};

};

#endif //SYSTEM_H