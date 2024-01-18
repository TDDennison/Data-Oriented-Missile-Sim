#include <algorithm>

#include "System.h"

System::System() {}

// Initialize the System — This happens *before* the game starts but *after* the world has been registered.
void System::Initialize() {};

// Called every game update
void System::Update(float dt) {};
void System::Update(float dt, float &dtOut) {};

// This entity fits our current requirements
void System::RegisterEntity(Entity entity) {
    registeredEntities.push_back(entity);
}

// This entity has stopped fitting our current requirements
void System::UnregisterEntity(Entity entity) {
    for (auto it = registeredEntities.begin(); it != registeredEntities.end(); ++it) {
        Entity e = *it;
        if (e.id == entity.id) {
        registeredEntities.erase(it);
        return;
        }
    }
}

// Unregister all entities that are no longer needed.
void System::UnregisterEntities()
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

// Compares two intervals according to starting times.
bool System::compareExecutionOrder(System *s1, System *s2)
{
    return (s1->executionOrder_ < s2->executionOrder_);
}

