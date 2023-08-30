#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include "ComponentManager.h"
#include "../Components/TransformComponent.h"
#include "Managers.h"
#include "../Utilities.h"

class TransformManager : public ComponentManager<TransformComponent, MaxComponents>
{
    public:

    static TransformManager* GetInstance();
    void WriteToLog(float time);

    private:
    TransformManager(){};
    inline static TransformManager* instance = nullptr;
    std::string name_;
};


#endif //TRANSFORM_MANAGER_H