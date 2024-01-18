#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

#include "ComponentManager.h"
#include "ClockComponent.h"
#include "ManagersConstants.h"

#include <memory>

class ClockManager : public ComponentManager<ClockComponent, Managers::Constants::MaxComponents>
{
    public:

    ClockManager();

    void UpdateClocks(real dt);
};

#endif //CLOCK_MANAGER_H