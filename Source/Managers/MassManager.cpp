#include "MassManager.h"

MassManager* MassManager::GetInstance() {
    if(instance == nullptr) { instance = new MassManager(); }
    return instance;
}

void MassManager::WriteToLog(float time)
{
    std::cout << "===== MassManager Log t = " << time << " =====" << std::endl;
    for(std::map<unsigned int, unsigned int>::iterator iter = entityMap.begin(); iter != entityMap.end(); ++iter)
    {
        unsigned int key =  iter->first;

        unsigned int index = entityMap[key];            
        MassComponent massComponent = componentData.data[index];

        std::cout << "     Entity: " << key << std::endl;
        std::cout << "          Component ID: " << massComponent.getId() << std::endl;
        std::cout << "          mass: " << massComponent.mass << std::endl;
    }

    std::cout << std::endl;
}