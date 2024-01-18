#ifndef ACCUMULATOR_MANAGER_H
#define ACCUMULATOR_MANAGER_H

#include <memory>

#include "AccumulatorComponent.h"
#include "MassComponent.h"
#include "TransformComponent.h"
#include "Utilities.h"

#include "ComponentManager.h"
#include "ManagersConstants.h"
#include "MassManager.h"
#include "TransformManager.h"

class AccumulatorManager : public ComponentManager<AccumulatorComponent, Managers::Constants::MaxComponents>
{
    public:
    static AccumulatorManager* GetInstance();

    // Adds a force at a point on the entity that is located at the center of gravity. This does not
    // produce any rotational effects.
    void AddForceAtCG(const Entity &entity, const Vector3 &force_eci);

    void ClearAccumulators();

    private:
    AccumulatorManager(MassManager *massManager, TransformManager *transformManager);
    inline static AccumulatorManager* instance = nullptr;

    MassManager* massManager_;
    TransformManager* transformManager_;
};

#endif //ACCUMULATOR_MANAGER_H