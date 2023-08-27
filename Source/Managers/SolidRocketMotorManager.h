#ifndef SOLID_ROCKET_MOTOR_MANAGER_H
#define SOLID_ROCKET_MOTOR_MANAGER_H

#include "ComponentManager.h"
#include "../Components/SolidRocketMotorComponent.h"
#include "../Components/Utilities.h"
#include "Managers.h"
#include "../Utilities.h"

class SolidRocketMotorManager : public ComponentManager<SolidRocketMotorComponent, MaxComponents>
{
    public:

    SolidRocketMotorManager(BoosterType type)
    {
        switch(type)
        {
            case FIRST_STAGE:
                name_ = "FS";
                break;
            case SECOND_STAGE:
                name_ = "SS";
                break;
        }
    }

    void WriteToLog(float time)
    {
        std::cout << "===== " << name_ << " SolidRocketMotorManager Log t = " << time << " =====" << std::endl;
        for(std::map<unsigned int, unsigned int>::iterator iter = entityMap.begin(); iter != entityMap.end(); ++iter)
        {
            unsigned int key =  iter->first;

            unsigned int index = entityMap[key];            
            SolidRocketMotorComponent srmComponent = componentData.data[index];

            std::cout << "     Entity: " << key << std::endl;
            std::cout << "          Component ID: " << srmComponent.getIdBitset() << std::endl;
            std::cout << "          " << ComponentUtilities::DecomposeComponentId(srmComponent.getId()) << std::endl;
            std::cout << "          interMass: " << srmComponent.inertMass << std::endl;
            std::cout << "          propellantMass: " << srmComponent.propellantMass << std::endl;
            std::cout << "          thrust: " << srmComponent.thrust << std::endl;
        }

        std::cout << std::endl;
    }

    private:
    std::string name_;
};

#endif //SOLID_ROCKET_MOTOR_MANAGER_H