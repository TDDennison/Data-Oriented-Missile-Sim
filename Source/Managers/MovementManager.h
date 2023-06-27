#ifndef MOVEMENT_MANAGER_H
#define MOVEMENT_MANAGER_H

#include "ComponentManager.h"
#include "../Components/MovementComponent.h"
#include "Managers.h"

class MovementManager : public ComponentManager<MovementComponent, MaxComponents>
{
    public:

    void WriteToLog(float time)
    {
        std::cout << "===== MovementManager Log t = " << time << " =====" << std::endl;
        for(std::map<unsigned int, unsigned int>::iterator iter = entityMap.begin(); iter != entityMap.end(); ++iter)
        {
            unsigned int key =  iter->first;

            unsigned int index = entityMap[key];            
            MovementComponent moveComponent = componentData.data[index];

            std::cout << "     Entity: " << key << std::endl;
            std::cout << "          Component ID: " << moveComponent.componentId << std::endl;
            std::cout << "          velocity.x: " << moveComponent.velocity_eci.x << std::endl;
            std::cout << "          velocity.y: " << moveComponent.velocity_eci.y << std::endl;
            std::cout << "          velocity.z: " << moveComponent.velocity_eci.z << std::endl;
            std::cout << "          acceleration.x: " << moveComponent.acceleration_eci.x << std::endl;
            std::cout << "          acceleration.y: " << moveComponent.acceleration_eci.y << std::endl;
            std::cout << "          acceleration.z: " << moveComponent.acceleration_eci.z << std::endl;
        }

        std::cout << std::endl;
    }
};

#endif //MOVEMENT_MANAGER_H