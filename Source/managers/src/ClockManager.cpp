#include "ClockManager.h"

ClockManager::ClockManager() : ComponentManager("ClockManager") {}

void ClockManager::UpdateClocks(real dt)
{
    for(std::map<unsigned int, unsigned int>::iterator iter = entityMap.begin(); iter != entityMap.end(); ++iter)
    {
        unsigned int key =  iter->first;

        unsigned int index = entityMap[key];            
        ClockComponent& clockComponent = componentData.data[index];
        clockComponent.time += dt;
    }
}
