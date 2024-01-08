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
    MassManager() : ComponentManager("MassManager") {};

    // Start: ILoggable Implementation
    // ================================================================================

    bool ParseBinaryToText(std::string fileName) override;

    // ================================================================================
    // End: ILoggable Implementation

    inline static MassManager* instance = nullptr;
};

#endif //MASS_MANAGER_H