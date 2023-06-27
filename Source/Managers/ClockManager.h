#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

#include "ComponentManager.h"
#include "../Components/ClockComponent.h"
#include "Managers.h"

class ClockManager : public ComponentManager<ClockComponent, MaxComponents>
{
    public:

    void UpdateClocks(real dt)
    {
        for(std::map<unsigned int, unsigned int>::iterator iter = entityMap.begin(); iter != entityMap.end(); ++iter)
        {
            unsigned int key =  iter->first;

            unsigned int index = entityMap[key];            
            ClockComponent& clockComponent = componentData.data[index];
            clockComponent.time += dt;
        }
    }
};

#endif //CLOCK_MANAGER_H