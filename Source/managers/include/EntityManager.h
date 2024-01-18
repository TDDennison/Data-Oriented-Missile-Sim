#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <string>
#include <vector>

#include "AccumulatorComponent.h"
#include "DomSimConstants.h"
#include "DomSimEnumerations.h"
#include "Entity.h"
#include "MassComponent.h"
#include "ManagersConstants.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "SolidRocketMotorManager.h"

struct QueueableEntity {
    QueueableEntity(DomSim::Enumerations::SystemType system, Entity ent) : systemType(system), entity(ent) {};

    DomSim::Enumerations::SystemType systemType;
    Entity entity;
};


class EntityManager
{
    public:
    static EntityManager* GetInstance();

    Entity CreateEntity();

    void CreateInertFSBoosterEntity(AccumulatorComponent &oldAcc, 
                                    MassComponent &oldMass,
                                    MovementComponent &oldMove,
                                    TransformComponent &oldTrans);

    void CreateInertSSBoosterEntity(AccumulatorComponent &oldAcc, 
                                    MassComponent &oldMass,
                                    MovementComponent &oldMove,
                                    TransformComponent &oldTrans);


    uint16_t getAccumIndexTracker();
    void resetAccumIndexTracker();
    AccumulatorComponent &getQueuedAccumulatorComponent(uint16_t index);

    uint16_t getMassIndexTracker();
    void resetMassIndexTracker();
    MassComponent &getQueuedMassComponent(uint16_t index);

    uint16_t getMovementIndexTracker();
    void resetMovementIndexTracker();
    MovementComponent &getQueuedMovementComponent(uint16_t index);

    uint16_t getTransformIndexTracker();
    void resetTransformIndexTracker();
    TransformComponent &getQueuedTransformComponent(uint16_t index);

    uint16_t getSSSRMIndexTracker();
    void resetSSSRMIndexTracker();
    SolidRocketMotorComponent &getQueuedSSSRMComponent(uint16_t index);


    uint16_t getNumQueuedEntities();
    void resetQueuedEntities();
    QueueableEntity &getQueuedEntity(uint16_t index);

    template<typename T>
    void QueueEntityAndComponentToRegister(DomSim::Enumerations::SystemType systemType, Entity entity, T& component) {
        QueueableEntity pair(systemType, entity);
        QueueEntityToRegister(pair);


        switch(systemType)
        {
            case DomSim::Enumerations::SystemType::SECOND_STAGE_BOOSTER:
            {
                QueueSSSRMComponentToRegister(static_cast<SolidRocketMotorComponent&>(component));
                break;
            }
            default: {
                std::cout << "Error when queueing entity and component to register. Investigate further." << std::endl;
                break;
            }
        }
    }

    private:
    EntityManager(){};

    void QueueAccumulatorComponentToRegister(AccumulatorComponent& component);
    void QueueMassComponentToRegister(MassComponent& component);
    void QueueMovementComponentToRegister(MovementComponent& component);
    void QueueSSSRMComponentToRegister(SolidRocketMotorComponent& component);
    void QueueTransformComponentToRegister(TransformComponent& component);

    void QueueEntityToRegister(QueueableEntity& pair);

    inline static EntityManager* instance = nullptr;

    inline static unsigned int nextId = 1;

    // ========== Components ==========

    uint16_t accumIndexTracker = 0;
    AccumulatorComponent accumulatorComponentsToRegister[Managers::Constants::MaxComponents];

    uint16_t massIndexTracker = 0;
    MassComponent massComponentsToRegister[Managers::Constants::MaxComponents];

    uint16_t moveIndexTracker = 0;
    MovementComponent movementComponentsToRegister[Managers::Constants::MaxComponents];

    uint16_t transformIndexTracker = 0;
    TransformComponent transformComponentsToRegister[Managers::Constants::MaxComponents];

    uint16_t ssSRMIndexTracker = 0;
    SolidRocketMotorComponent ssSRMComponentsToRegister[Managers::Constants::MaxComponents];


    // ========== Entities ==========
    std::vector<QueueableEntity> entitiesToRegister;

};

#endif //ENTITY_MANAGER_H

