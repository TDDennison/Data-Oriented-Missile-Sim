#ifndef ACCUMULATOR_MANAGER_H
#define ACCUMULATOR_MANAGER_H

#include <memory>

#include "../Components/AccumulatorComponent.h"
#include "../Components/MassComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/Utilities.h"

#include "ComponentManager.h"
#include "Managers.h"
#include "MassManager.h"
#include "TransformManager.h"

class AccumulatorManager : public ComponentManager<AccumulatorComponent, MaxComponents>
{
    public:
    static AccumulatorManager* GetInstance() {
        if(instance == nullptr) { instance = new AccumulatorManager(MassManager::GetInstance(), TransformManager::GetInstance()); }
        return instance;
    }

    // Adds a force at a point on the entity that is located at the center of gravity. This does not
    // produce any rotational effects.
    void AddForceAtCG(const Entity &entity, const Vector3 &force_eci)
    {
        AccumulatorComponent& accumulatorComponent = Lookup(entity);

        accumulatorComponent.forceAccumulator_eci += force_eci;
    }

    void ClearAccumulators()
    {
        for (auto & accComp : componentData.data)
        {
            accComp.forceAccumulator_eci.x = 0.0;
            accComp.forceAccumulator_eci.y = 0.0;
            accComp.forceAccumulator_eci.z = 0.0;

            accComp.torqueAccumulator_eci.x = 0.0;
            accComp.torqueAccumulator_eci.y = 0.0;
            accComp.torqueAccumulator_eci.z = 0.0;
        }
    }

    private:
    AccumulatorManager(MassManager *massManager, TransformManager *transformManager) : ComponentManager("AccumulatorManager"), massManager_(massManager), transformManager_(transformManager) {}
    inline static AccumulatorManager* instance = nullptr;

    MassManager* massManager_;
    TransformManager* transformManager_;
};

#endif //ACCUMULATOR_MANAGER_H