#ifndef ACCUMULATOR_COMPONENT_H
#define ACCUMULATOR_COMPONENT_H

#include "Component.h"
#include "../MathTypes/Vector3.h"

struct AccumulatorComponent : public Component
{
    // Constructors
    AccumulatorComponent() : Component(DEFAULT_COMPONENT_ID) {}
    AccumulatorComponent(uint16_t id) : Component(id) {}

    // Holds the accumulated forces for an entity in a frame defined in the ECI frame.
    Vector3 forceAccumulator_eci{};

    // Holds the accumulated torques for an entity in a frame defined in the ECI frame.
    Vector3 torqueAccumulator_eci{};

    // The direction of the force is expected in ECI coordinates
    // AND the whereas the application point is expected in ECI coordinates.
    void AddForceAtPoint(const Vector3 &force_eci, const Vector3 &application_point_eci, Vector3 &position_cg_eci) {
        // Compute the moment arm.
        Vector3 point = application_point_eci;
        point -= position_cg_eci;

        // Add the linear force.
        forceAccumulator_eci += force_eci;

        // Compute the generated torque.
        torqueAccumulator_eci += point % force_eci;
    }

};

#endif //ACCUMULATOR_COMPONENT_H