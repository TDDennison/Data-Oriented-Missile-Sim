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

    SolidRocketMotorManager(std::string logFileName, BoosterType type) : ComponentManager(logFileName)
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

    private:
    std::string name_;
};

#endif //SOLID_ROCKET_MOTOR_MANAGER_H