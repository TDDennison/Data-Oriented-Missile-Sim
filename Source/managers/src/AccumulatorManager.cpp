#include "AccumulatorManager.h"

AccumulatorManager::AccumulatorManager(MassManager *massManager, TransformManager *transformManager) : ComponentManager("AccumulatorManager"), massManager_(massManager), transformManager_(transformManager) {}

AccumulatorManager* AccumulatorManager::GetInstance() {
    if(instance == nullptr) { instance = new AccumulatorManager(MassManager::GetInstance(), TransformManager::GetInstance()); }
    return instance;
}

// Adds a force at a point on the entity that is located at the center of gravity. This does not
// produce any rotational effects.
void AccumulatorManager::AddForceAtCG(const Entity &entity, const Vector3 &force_eci)
{
    AccumulatorComponent& accumulatorComponent = Lookup(entity);

    accumulatorComponent.forceAccumulator_eci += force_eci;
}

void AccumulatorManager::ClearAccumulators()
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
