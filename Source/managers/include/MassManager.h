#ifndef MASS_MANAGER_H
#define MASS_MANAGER_H

#include "ComponentManager.h"
#include "MassComponent.h"
#include "ManagersConstants.h"

class MassManager : public ComponentManager<MassComponent, Managers::Constants::MaxComponents>
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