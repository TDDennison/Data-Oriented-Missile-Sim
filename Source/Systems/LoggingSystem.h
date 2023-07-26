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

    LoggingSystem() {
        massManager_ = MassManager::GetInstance();
        movementManager_ = MovementManager::GetInstance();
        transformManager_ = TransformManager::GetInstance();
    }

    void WriteAllLogs(float time)
    {
        massManager_->WriteToLog(time);
        movementManager_->WriteToLog(time);
        // firstStageManager->WriteToLog(time);
        // secondStageManager->WriteToLog(time);
        transformManager_->WriteToLog(time);
    }
    
    MassManager* massManager_;
    MovementManager* movementManager_;
    SolidRocketMotorManager* firstStageManager_;
    SolidRocketMotorManager* secondStageManager_;
    TransformManager* transformManager_;
};

#endif //LOGGING_SYSTEM_H