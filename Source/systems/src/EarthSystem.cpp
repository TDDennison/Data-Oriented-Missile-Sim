#include "EarthSystem.h"

EarthSystem::EarthSystem(AccumulatorManager& accumulatorManager,
            MassManager& massManager,
            TransformManager& transformManager) : 
            accumulatorManager_(accumulatorManager),
            massManager_(massManager),
            transformManager_(transformManager),
            System() {};


EarthSystem* EarthSystem::GetInstance() {
    if(instance == nullptr) { instance = new EarthSystem(*AccumulatorManager::GetInstance(), *MassManager::GetInstance(), *TransformManager::GetInstance()); }
    return instance;
}


void EarthSystem::Initialize() {
    // Grab the necessary attribtues.
    AttributesManager *attributesManager = AttributesManager::GetInstance();

    executionOrder_ = attributesManager->GetAttribute<uint16_t>(DomSim::Constants::EXECUTION_ORDER_EARTH_SYSTEM);

    std::cout << "Earth system execution order is: " << executionOrder_ << std::endl;
}


void EarthSystem::Update(float dt) {

    return;
    for (auto & entity : registeredEntities) {
        // Impart the forces produced by the Earth on entities here.
        // Rotational forces
        // Gravitational forces

        // Very basic gravity force.
        MassComponent& massComponent = massManager_.Lookup(entity);
        TransformComponent& transComponent = transformManager_.Lookup(entity);

        // Compute the force of gravity on the entity.
        real distance = Utilities::CalculateDistance(EARTH_POSITION, transComponent.position_eci);

        if (distance > 0.0)
        {
            real distance_squared = distance * distance;
            real gforce = (GRAVITATIONAL_CONSTANT * EARTH_MASS_KG * massComponent.mass) / distance_squared;

            // Calculate the direction of the force.
            Vector3 gforce_direction = transComponent.position_eci;
            gforce_direction.Normalize();
            gforce_direction *= -1 * gforce;
            accumulatorManager_.AddForceAtCG(entity, gforce_direction);
        }

    }
}


EarthSystem::Attributes::Attributes() {
    std::cout << "Earth System adding attributes." << std::endl;
    AttributesManager *attributesManager = AttributesManager::GetInstance();

    attributesManager->AddAttribute<uint16_t>(DomSim::Constants::EXECUTION_ORDER_EARTH_SYSTEM, Core::Enumerations::AttributeType::UINT16, DomSim::Constants::DEFAULT_UINT16);
}
