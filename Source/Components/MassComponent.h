#ifndef MASS_COMPONENT_H
#define MASS_COMPONENT_H

#include "Component.h"
#include "../Core/TypeDefinitions.h"
#include "../MathTypes/Matrix3.h"
#include "../MathTypes/Vector3.h"

struct MassComponent : public Component
{
    // Constructors
    MassComponent() : Component(DEFAULT_COMPONENT_ID) {}
    MassComponent(uint16_t id) : Component(id) {}

    real mass; // kg

    // The position of the entity's center of gravity in the ECI frame.
    Vector3 position_cg_eci{};

    // Inertia tensor of an entity. All values in the tensor are in the body frame.
    Matrix3 inertiaTensor{};
};

#endif //MASS_COMPONENT_H