#include "AccumulatorComponent.h"

AccumulatorComponent::AccumulatorComponent() : Component(DEFAULT_COMPONENT_ID) {}

AccumulatorComponent::AccumulatorComponent(AccumulatorComponent& other) : Component(other.getId()) {
    forceAccumulator_eci = other.forceAccumulator_eci;
    torqueAccumulator_eci = other.torqueAccumulator_eci;
}

AccumulatorComponent::AccumulatorComponent(uint16_t id) : Component(id) {}


void AccumulatorComponent::AddForceAtPoint(const Vector3 &force_eci, const Vector3 &application_point_eci, Vector3 &position_cg_eci) {
    // Compute the moment arm.
    Vector3 point = application_point_eci;
    point -= position_cg_eci;

    // Add the linear force.
    forceAccumulator_eci += force_eci;

    // Compute the generated torque.
    torqueAccumulator_eci += point % force_eci;
}