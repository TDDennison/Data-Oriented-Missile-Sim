// STL Includes
#include <iostream>
#include <memory.h>

#include "MassComponent.h"

MassComponent::MassComponent() : Component(DEFAULT_COMPONENT_ID) {}


MassComponent::MassComponent(MassComponent& other) : Component(other.getId()) {
    mass = other.mass;
    position_cg_body = other.position_cg_body;
    inertiaTensor = other.inertiaTensor;
    hasRoom = other.hasRoom;
    hasChanged = other.hasChanged;
    numSubMasses = other.numSubMasses;

    for (uint8_t i = 0; i < ComponentUtilities::MAX_SUB_MASSES; ++i)
    {
        subMasses[i] = other.subMasses[i];
    }


    memcpy(subMassDesignators, other.subMassDesignators, sizeof(subMassDesignators));
}


MassComponent::MassComponent(uint16_t id) : Component(id) {}


void MassComponent::AddSubmass(ComponentUtilities::ComponentDesignators designator, std::shared_ptr<MassComponent> component)
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


void MassComponent::RemoveSubmass(ComponentUtilities::ComponentDesignators designator)
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


void MassComponent::DecrementMass(float number)
{
    mass -= number;
}


void MassComponent::DecrementSubMass(float number, ComponentUtilities::ComponentDesignators designator)
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
