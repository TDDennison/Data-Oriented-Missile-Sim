#include "ComponentUtilities.h"

unsigned short ComponentUtilities::CreateComponentId(unsigned int missileId, unsigned short compDesignator)
{
    return (missileId << 8) | compDesignator;
}

std::string ComponentUtilities::DecomposeComponentId(unsigned short componentId)
{
    std::stringstream stream;
    unsigned short missileId = (componentId >> 8) & 0xFF;

    //std::map<ComponentDesignators, std::string>::iterator itr = 
    std::string componentName = DesignatorsToStrings.at(static_cast<ComponentDesignators>(componentId & 0xFF));
    stream << "Missile: " << missileId << "\t";
    stream << "Component Type: " << componentName;

    return stream.str();
}
