#ifndef LOGGING_SYSTEM_H
#define LOGGING_SYSTEM_H

#include "System.h"

#include "../Managers/MassManager.h"
#include "../Managers/MovementManager.h"
#include "../Managers/SolidRocketMotorManager.h"
#include "../Managers/TransformManager.h"

class LoggingSystem : public System
{
    public:

    void WriteAllLogs(float time)
    {
        massManager->WriteToLog(time);
        movementManager->WriteToLog(time);
        // firstStageManager->WriteToLog(time);
        // secondStageManager->WriteToLog(time);
        transformManager->WriteToLog(time);
    }
    
    MassManager* massManager;
    MovementManager* movementManager;
    SolidRocketMotorManager* firstStageManager;
    SolidRocketMotorManager* secondStageManager;
    TransformManager* transformManager;
};

#endif //LOGGING_SYSTEM_H