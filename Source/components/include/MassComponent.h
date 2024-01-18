#ifndef MASS_COMPONENT_H
#define MASS_COMPONENT_H

#include <map>

#include "Component.h"
#include "Utilities.h"
#include "Configurations.h"
#include "TypeDefinitions.h"
#include "Matrix3.h"
#include "Vector3.h"

#include "ComponentUtilities.h"

class MassComponent : public Component
{
    public:

    // Constructors
    MassComponent();
    MassComponent(MassComponent& other);
    MassComponent(uint16_t id);

    void AddSubmass(ComponentUtilities::ComponentDesignators designator, std::shared_ptr<MassComponent> component);

    void RemoveSubmass(ComponentUtilities::ComponentDesignators designator);

    void DecrementMass(float number);

    void DecrementSubMass(float number, ComponentUtilities::ComponentDesignators designator);

    real mass; // kg

    // The position of the entity's center of gravity in its own body frame.
    Vector3 position_cg_body{};

    // Inertia tensor of an entity. All values in the tensor are in the body frame.
    Matrix3 inertiaTensor{};

    bool hasRoom = true;
    bool hasChanged = false;

    // All sub-masses that make up this total mass.
    uint8_t numSubMasses = 0;
    std::shared_ptr<MassComponent> subMasses[ComponentUtilities::MAX_SUB_MASSES];

    private:
    ComponentUtilities::ComponentDesignators subMassDesignators[ComponentUtilities::MAX_SUB_MASSES]{ComponentUtilities::ComponentDesignators::NONE};
};

#endif //MASS_COMPONENT_H