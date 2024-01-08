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

    void AddSubmass(ComponentUtilities::ComponentDesignators designator, std::shared_ptr<MassComponent> component)
    {
        // Make sure the sub mass tracker isn't already full.
        if(hasRoom)
        {
            ++numSubMasses;

            // Find the first unoccupied submass index.
            for(uint8_t i = 0; i < ComponentUtilities::MAX_SUB_MASSES; ++i)
            {
                if(subMassDesignators[i] == ComponentUtilities::ComponentDesignators::NONE)
                {
                    subMassDesignators[i] = designator;
                    subMasses[i] = component;
                    mass += component->mass;
                    break;
                }
            }
        }
        else {
            // TODO: Throw an exception or something better here.
            std::cout << "Attempted to add submass but there was no room left!" << std::endl;
        }

    }

    void RemoveSubmass(ComponentUtilities::ComponentDesignators designator)
    {
        // Find the submass with the designator
        for(uint8_t i = 0; i < ComponentUtilities::MAX_SUB_MASSES; ++i)
        {
            if(subMassDesignators[i] == designator)
            {
                --numSubMasses;
                mass -= subMasses[i]->mass;
                subMassDesignators[i] = ComponentUtilities::ComponentDesignators::NONE;
                subMasses[i].reset();
            }
        }
    }

    void DecrementMass(float number)
    {
        mass -= number;
    }

    void DecrementSubMass(float number, ComponentUtilities::ComponentDesignators designator)
    {

        // Find the submass with the designator
        for(uint8_t i = 0; i < ComponentUtilities::MAX_SUB_MASSES; ++i)
        {
            if(subMassDesignators[i] == designator)
            {
                subMasses[i]->mass -= number; // Decrement the mass of the submass
                subMasses[i]->hasChanged = true;

                mass -= number; // Decrement the mass of the total mass
            }
        }
    }

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