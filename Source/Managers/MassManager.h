#ifndef MASS_MANAGER_H
#define MASS_MANAGER_H

#include "ComponentManager.h"
#include "../Components/MassComponent.h"
#include "Managers.h"

class MassManager : public ComponentManager<MassComponent, MaxComponents>
{
    public:

    static MassManager* GetInstance();

    private:
    MassManager() : ComponentManager("MassManager.bin") {};
    inline static MassManager* instance = nullptr;
};

#endif //MASS_MANAGER_H