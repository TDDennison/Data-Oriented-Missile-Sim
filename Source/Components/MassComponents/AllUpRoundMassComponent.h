#ifndef ALL_UP_ROUND_MASS_COMPONENT_H
#define ALL_UP_ROUND_MASS_COMPONENT_H

#include "MassComponent.h"

class AllUpRoundMassComponent : public MassComponent
{
    // Constructors
    AllUpRoundMassComponent(MassComponent fsMass, MassComponent ssMass, MassComponent plMass) : 
                            firstStageMassComponent_(fsMass), 
                            secondStageMassComponent_(ssMass), 
                            payloadMassComponent_(plMass), MassComponent(DEFAULT_COMPONENT_ID) {}
    AllUpRoundMassComponent(MassComponent fsMass, MassComponent ssMass, MassComponent plMass, uint16_t id) : 
                            firstStageMassComponent_(fsMass), 
                            secondStageMassComponent_(ssMass), 
                            payloadMassComponent_(plMass), MassComponent(id) {}

    MassComponent firstStageMassComponent_{};
    MassComponent secondStageMassComponent_{};
    MassComponent payloadMassComponent_{};
};

#endif //ALL_UP_ROUND_MASS_COMPONENT_H