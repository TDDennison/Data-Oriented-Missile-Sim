#ifndef MOVEMENT_MANAGER_H
#define MOVEMENT_MANAGER_H

#include "ComponentManager.h"
#include "MovementComponent.h"
#include "ManagersConstants.h"

class MovementManager : public ComponentManager<MovementComponent, Managers::Constants::MaxComponents>
{
    public:

    static MovementManager* GetInstance();

    private:
    MovementManager() : ComponentManager("MovementManager") {};
    inline static MovementManager* instance = nullptr;
};

#endif //MOVEMENT_MANAGER_H