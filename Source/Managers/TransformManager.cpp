#include <memory>

#include "../Components/Utilities.h"
#include "TransformManager.h"

TransformManager* TransformManager::GetInstance() {
    if(instance == nullptr) {
        instance = new TransformManager(); 
    }
    return instance;
}

// void TransformManager::WriteToLog(float time)
// {
//     std::cout << "===== " << name_ << " TransformManager Log t = " << time << " =====" << std::endl;
//     for(std::map<unsigned int, unsigned int>::iterator iter = entityMap.begin(); iter != entityMap.end(); ++iter)
//     {
//         unsigned int key =  iter->first;

//         unsigned int index = entityMap[key];            
//         TransformComponent transformComponent = componentData.data[index];

//         std::cout << "     Entity: " << key << std::endl;
//         std::cout << "          Component ID: " << transformComponent.getIdBitset() << std::endl;
//         std::cout << "          " << ComponentUtilities::DecomposeComponentId(transformComponent.getId()) << std::endl;
//         std::cout << "          position.x: " << transformComponent.position_eci.x << std::endl;
//         std::cout << "          position.y: " << transformComponent.position_eci.y << std::endl;
//         std::cout << "          position.z: " << transformComponent.position_eci.z << std::endl;
//     }

//     std::cout << std::endl;
// }
