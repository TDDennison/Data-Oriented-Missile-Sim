#ifndef ACCUMULATOR_MANAGER_H
#define ACCUMULATOR_MANAGER_H

#include "../Components/AccumulatorComponent.h"
#include "../Components/MassComponent.h"
#include "../Components/TransformComponent.h"

#include "ComponentManager.h"
#include "Managers.h"
#include "MassManager.h"
#include "TransformManager.h"

class AccumulatorManager : public ComponentManager<AccumulatorComponent, MaxComponents>
{
    public:

    AccumulatorManager(MassManager *massManager, TransformManager *transformManager) : massManager_(massManager), transformManager_(transformManager) {}

    void WriteToLog(float time)
    {
        std::cout << "===== AccumulatorComponent Log t = " << time << " =====" << std::endl;
        for(std::map<unsigned int, unsigned int>::iterator iter = entityMap.begin(); iter != entityMap.end(); ++iter)
        {
            unsigned int key =  iter->first;

            unsigned int index = entityMap[key];            
            AccumulatorComponent accumulatorComponent = componentData.data[index];

            std::cout << "     Entity: " << key << std::endl;
            std::cout << "          Component ID: " << accumulatorComponent.componentId << std::endl;
            std::cout << "          Accumulated force x: " << accumulatorComponent.forceAccumulator_eci.x << std::endl;
            std::cout << "          Accumulated force y: " << accumulatorComponent.forceAccumulator_eci.y << std::endl;
            std::cout << "          Accumulated force z: " << accumulatorComponent.forceAccumulator_eci.z << std::endl;
            std::cout << "          Accumulated torque x: " << accumulatorComponent.torqueAccumulator_eci.x << std::endl;
            std::cout << "          Accumulated torque y: " << accumulatorComponent.torqueAccumulator_eci.y << std::endl;
            std::cout << "          Accumulated torque z: " << accumulatorComponent.torqueAccumulator_eci.z << std::endl;
        }

        std::cout << std::endl;
    }

    // Adds a force at a point on the entity that is located at the center of gravity. This does not
    // produce any rotational effects.
    void AddForceAtCG(const Entity &entity, const Vector3 &force_eci)
    {
        AccumulatorComponent& accumulatorComponent = Lookup(entity);

        accumulatorComponent.forceAccumulator_eci += force_eci;
    }

    // Adds a force at a point on the entity that is not located at the center of gravity of the body
    // resulting in linear and rotational effects.
    void AddForceAtPoint(const Entity &entity, const Vector3 &force_eci, const Vector3 &point_eci)
    {
        AccumulatorComponent& accumulatorComponent = Lookup(entity);
        MassComponent& massComponent = massManager_->Lookup(entity);

        // Calculate the moment arm.
        Vector3 momentArm_eci = point_eci;
        momentArm_eci -= massComponent.position_cg_eci;

        accumulatorComponent.forceAccumulator_eci += force_eci;
        accumulatorComponent.torqueAccumulator_eci += momentArm_eci % force_eci;
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
    MassManager* massManager_;
    TransformManager* transformManager_;
};

#endif //ACCUMULATOR_MANAGER_H