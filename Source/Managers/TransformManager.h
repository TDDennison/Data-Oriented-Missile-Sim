#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include "ComponentManager.h"
#include "../Components/TransformComponent.h"
#include "Managers.h"
#include "../Utilities.h"

class TransformManager : public ComponentManager<TransformComponent, MaxComponents>
{
    public:

    void WriteToLog(float time)
    {
        std::cout << "===== " << name_ << " TransformManager Log t = " << time << " =====" << std::endl;
        for(std::map<unsigned int, unsigned int>::iterator iter = entityMap.begin(); iter != entityMap.end(); ++iter)
        {
            unsigned int key =  iter->first;

            unsigned int index = entityMap[key];            
            TransformComponent transformComponent = componentData.data[index];

            std::cout << "     Entity: " << key << std::endl;
            std::cout << "          Component ID: " << transformComponent.getId() << std::endl;
            std::cout << "          position.x: " << transformComponent.position_eci.x << std::endl;
            std::cout << "          position.y: " << transformComponent.position_eci.y << std::endl;
            std::cout << "          position.z: " << transformComponent.position_eci.z << std::endl;
        }

        std::cout << std::endl;
    }

    private:
    std::string name_;
};


#endif //TRANSFORM_MANAGER_H