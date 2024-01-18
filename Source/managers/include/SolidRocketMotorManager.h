#ifndef SOLID_ROCKET_MOTOR_MANAGER_H
#define SOLID_ROCKET_MOTOR_MANAGER_H

#include "ComponentManager.h"
#include "DomSimEnumerations.h"
#include "SolidRocketMotorComponent.h"
#include "Utilities.h"
#include "ManagersConstants.h"

class SolidRocketMotorManager : public ComponentManager<SolidRocketMotorComponent, Managers::Constants::MaxComponents>
{
    public:

    SolidRocketMotorManager(std::string logFileName, DomSim::Enumerations::BoosterType type);

    // Start: ILoggable Implementation
    // ================================================================================
    bool ParseBinaryToText(std::string fileName) override;

    // ================================================================================
    // End: ILoggable Implementation


    private:
    std::string name_;
};

#endif //SOLID_ROCKET_MOTOR_MANAGER_H