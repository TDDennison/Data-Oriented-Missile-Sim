#ifndef EARTH_SYSTEM_H
#define EARTH_SYSTEM_H

#include <iostream>

#include "System.h"

#include "AccumulatorComponent.h"
#include "MovementComponent.h"
#include "TransformComponent.h"

#include "AttributesManager.h"
#include "TypeDefinitions.h"

#include "AccumulatorManager.h"
#include "MassManager.h"
#include "MovementManager.h"
#include "TransformManager.h"

#include "Vector3.h"

class EarthSystem : public System
{
    public:
    static EarthSystem* GetInstance();

    void Initialize() override;
    
    void Update(float dt, bool &allowMassDecrement) override;

    const Vector3 EARTH_POSITION{0.0, 0.0, 0.0};
    static constexpr real GRAVITATIONAL_CONSTANT = 0.0000000000667f;
    static constexpr real EARTH_MASS_KG = 5.972e+24f;

    private:

    EarthSystem(AccumulatorManager& accumulatorManager,
                MassManager& massManager,
                TransformManager& transformManager);
    inline static EarthSystem* instance = nullptr;

    // Private class used to register attributes prior to runtime starting.
    // This is done through the use of static construction of this class.
    class Attributes
    {
        public:
        Attributes();
    };

    inline static const Attributes attributes{}; // Static constructor used to register attributes before main() is started.

    AccumulatorManager& accumulatorManager_;
    MassManager& massManager_;
    TransformManager& transformManager_;
};
#endif //EARTH_SYSTEM_H