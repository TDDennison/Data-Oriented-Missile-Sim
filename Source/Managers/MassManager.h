#ifndef MASS_MANAGER_H
#define MASS_MANAGER_H

#include "ComponentManager.h"
#include "../Components/MassComponent.h"
#include "Managers.h"

class MassManager : public ComponentManager<MassComponent, MaxComponents>
{
    public:

    void WriteToLog(float time)
    {
        std::cout << "===== MassManager Log t = " << time << " =====" << std::endl;
        for(std::map<unsigned int, unsigned int>::iterator iter = entityMap.begin(); iter != entityMap.end(); ++iter)
        {
            unsigned int key =  iter->first;

            unsigned int index = entityMap[key];            
            MassComponent massComponent = componentData.data[index];

            std::cout << "     Entity: " << key << std::endl;
            std::cout << "          Component ID: " << massComponent.componentId << std::endl;
            std::cout << "          mass: " << massComponent.mass << std::endl;
        }

        std::cout << std::endl;
    }
};

#endif //MASS_MANAGER_H