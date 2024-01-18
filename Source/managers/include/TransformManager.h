#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include "ComponentManager.h"
#include "ManagersConstants.h"
#include "TransformComponent.h"

class TransformManager : public ComponentManager<TransformComponent, Managers::Constants::MaxComponents>
{
    public:

    static TransformManager* GetInstance();

    private:
    TransformManager() : ComponentManager("TransformManager") {};
    inline static TransformManager* instance = nullptr;
    std::string name_;
};


#endif //TRANSFORM_MANAGER_H