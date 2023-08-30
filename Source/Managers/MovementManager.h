#ifndef MOVEMENT_MANAGER_H
#define MOVEMENT_MANAGER_H

#include "ComponentManager.h"
#include "../Components/MovementComponent.h"
#include "Managers.h"

class MovementManager : public ComponentManager<MovementComponent, MaxComponents>
{
    public:

    static MovementManager* GetInstance();
    void WriteToLog(float time);

    private:
    MovementManager(){};
    inline static MovementManager* instance = nullptr;
};

#endif //MOVEMENT_MANAGER_H