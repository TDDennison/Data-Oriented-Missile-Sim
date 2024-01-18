#include "MovementComponent.h"

MovementComponent::MovementComponent() : Component(DEFAULT_COMPONENT_ID) {}

MovementComponent::MovementComponent(MovementComponent& other) : Component(other.getId()) {
    velocity_eci = other.velocity_eci;
    acceleration_eci = other.acceleration_eci;
    angular_velocity_eci = other.angular_velocity_eci;
    angular_acceleration_eci = other.angular_acceleration_eci;

}

MovementComponent::MovementComponent(uint16_t id) : Component(id) {}
