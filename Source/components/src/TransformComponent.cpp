#include "TransformComponent.h"

TransformComponent::TransformComponent() : Component(DEFAULT_COMPONENT_ID) {}

TransformComponent::TransformComponent(TransformComponent& other) : Component(other.getId()) {
    position_eci = other.position_eci;
    orientation_eci = other.orientation_eci;
    transformMatrix = other.transformMatrix;
}

TransformComponent::TransformComponent(uint16_t id) : Component(id) {}
