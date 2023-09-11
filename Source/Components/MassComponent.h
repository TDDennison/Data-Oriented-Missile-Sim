#ifndef MASS_COMPONENT_H
#define MASS_COMPONENT_H

#include <map>

#include "Component.h"
#include "Utilities.h"
#include "../Core/Configurations.h"
#include "../Core/TypeDefinitions.h"
#include "../MathTypes/Matrix3.h"
#include "../MathTypes/Vector3.h"

struct MassComponent : public Component
{
    // Constructors
    MassComponent() : Component(DEFAULT_COMPONENT_ID) {}
    MassComponent(uint16_t id) : Component(id) {}

    void AddSubmass(ComponentUtilities::ComponentDesignators designator, MassComponent component)
    {
        ++numSubMasses;
        subMasses[designator] = component;
        mass += component.mass;
    }

    void RemoveSubmass(ComponentUtilities::ComponentDesignators designator)
    {
        --numSubMasses;
        mass -= subMasses[designator].mass;
        subMasses.erase(designator);
    }

    void DecrementMass(float number)
    {
        mass -= number;
    }

    void DecrementSubMass(float number, ComponentUtilities::ComponentDesignators designator)
    {
        MassComponent &component = subMasses[designator];
        component.mass -= number;
        component.hasChanged = true;

        mass -= number;
    }

    real mass; // kg

    // The position of the entity's center of gravity in its own body frame.
    Vector3 position_cg_body{};

    // Inertia tensor of an entity. All values in the tensor are in the body frame.
    Matrix3 inertiaTensor{};

    bool hasChanged = false;

    // All sub-masses that make up this total mass.
    uint8_t numSubMasses = 0;
    std::map<ComponentUtilities::ComponentDesignators, MassComponent> subMasses{};
};

#endif //MASS_COMPONENT_H