#ifndef MOTION_SYSTEM_TESTS_H
#define MOTION_SYSTEM_TESTS_H

#include "../../_Utilities/_Utilities.h"

#include "../../../Components/MovementComponent.h"
#include "../../../Components/TransformComponent.h"

#include "../../../Managers/AccumulatorManager.h"
#include "../../../Managers/EntityManager.h"
#include "../../../Managers/MassManager.h"
#include "../../../Managers/MovementManager.h"
#include "../../../Managers/TransformManager.h"

#include "../../../Systems/IntegrationSystem_Euler.h"

#include <cmath>

class IntegrationSystem_Euler_Tests
{
    public:
    
    static void IntegrationSystem_Euler_Test_BasicFallingObject_XDirection()
    {
        MassManager massManager;
        MovementManager movementManager;
        TransformManager transformManager;
        AccumulatorManager accumulatorManager(&massManager, &transformManager);
        IntegrationSystem_Euler integrationSystem(&accumulatorManager, &massManager, &movementManager, &transformManager);

        // Create the entity and its components.
        Entity entity = EntityManager::CreateEntity();

        AccumulatorComponent accumulatorComponent;
        accumulatorComponent.forceAccumulator_eci = {0.0, 0.0, 0.0};
        accumulatorComponent.torqueAccumulator_eci = {0.0, 0.0, 0.0};

        MassComponent massComponent;
        massComponent.mass = 1.0;
        massComponent.position_cg_eci = {10.0, 0.0, 0.0};
        massComponent.inertiaTensor = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

        MovementComponent moveComponent;
        moveComponent.velocity_eci = Vector3::Zero();
        moveComponent.acceleration_eci = {-1.0, 0.0, 0.0}; // Negative acceleration in x-direction only.

        TransformComponent transComponent;
        transComponent.position_eci = {10.0, 0.0, 0.0}; // Positioned 10 units in z-direction only.

        // Add the components to their managers.
        accumulatorManager.Add(entity, accumulatorComponent);
        transformManager.Add(entity, transComponent);
        massManager.Add(entity, massComponent);
        movementManager.Add(entity, moveComponent);

        // Register the entity with the system.
        integrationSystem.RegisterEntity(entity);

        // Update the system.
        float dt = 1.0;
        integrationSystem.Update(dt);

        MovementComponent& changedMove = movementManager.Lookup(entity);
        TransformComponent& changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{10.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{-1.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{-1.0, 0.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{9.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{-2.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{-1.0, 0.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{7.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{-3.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{-1.0, 0.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{4.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{-4.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{-1.0, 0.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{-5.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{-1.0, 0.0, 0.0}));

        PASSED();
    }

    static void IntegrationSystem_Euler_Test_BasicFallingObject_YDirection()
    {
        MassManager massManager;
        MovementManager movementManager;
        TransformManager transformManager;
        AccumulatorManager accumulatorManager(&massManager, &transformManager);
        IntegrationSystem_Euler integrationSystem(&accumulatorManager, &massManager, &movementManager, &transformManager);

        // Create the entity and its components.
        Entity entity = EntityManager::CreateEntity();

        AccumulatorComponent accumulatorComponent;
        accumulatorComponent.forceAccumulator_eci = {0.0, 0.0, 0.0};
        accumulatorComponent.torqueAccumulator_eci = {0.0, 0.0, 0.0};

        MassComponent massComponent;
        massComponent.mass = 1.0;
        massComponent.position_cg_eci = {0.0, 10.0, 0.0};
        massComponent.inertiaTensor = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

        MovementComponent moveComponent;
        moveComponent.velocity_eci = Vector3::Zero();
        moveComponent.acceleration_eci = {0.0, -1.0, 0.0}; // Negative acceleration in x-direction only.

        TransformComponent transComponent;
        transComponent.position_eci = {0.0, 10.0, 0.0}; // Positioned 10 units in z-direction only.

        // Add the components to their managers.
        accumulatorManager.Add(entity, accumulatorComponent);
        transformManager.Add(entity, transComponent);
        massManager.Add(entity, massComponent);
        movementManager.Add(entity, moveComponent);

        // Register the entity with the system.
        integrationSystem.RegisterEntity(entity);

        // Update the system.
        float dt = 1.0;
        integrationSystem.Update(dt);

        MovementComponent& changedMove = movementManager.Lookup(entity);
        TransformComponent& changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 10.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{0.0, -1.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, -1.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 9.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{0.0, -2.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, -1.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 7.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{0.0, -3.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, -1.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 4.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{0.0, -4.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, -1.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{0.0, -5.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, -1.0, 0.0}));

        PASSED();
    }

    static void IntegrationSystem_Euler_Test_BasicFallingObject_ZDirection()
    {
        MassManager massManager;
        MovementManager movementManager;
        TransformManager transformManager;
        AccumulatorManager accumulatorManager(&massManager, &transformManager);
        IntegrationSystem_Euler integrationSystem(&accumulatorManager, &massManager, &movementManager, &transformManager);

        // Create the entity and its components.
        Entity entity = EntityManager::CreateEntity();

        AccumulatorComponent accumulatorComponent;
        accumulatorComponent.forceAccumulator_eci = {0.0, 0.0, 0.0};
        accumulatorComponent.torqueAccumulator_eci = {0.0, 0.0, 0.0};

        MassComponent massComponent;
        massComponent.mass = 1.0;
        massComponent.position_cg_eci = {0.0, 0.0, 10.0};
        massComponent.inertiaTensor = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

        MovementComponent moveComponent;
        moveComponent.velocity_eci = Vector3::Zero();
        moveComponent.acceleration_eci = {0.0, 0.0, -1.0}; // Negative acceleration in x-direction only.

        TransformComponent transComponent;
        transComponent.position_eci = {0.0, 0.0, 10.0}; // Positioned 10 units in z-direction only.

        // Add the components to their managers.
        accumulatorManager.Add(entity, accumulatorComponent);
        transformManager.Add(entity, transComponent);
        massManager.Add(entity, massComponent);
        movementManager.Add(entity, moveComponent);

        // Register the entity with the system.
        integrationSystem.RegisterEntity(entity);
        // Update the system.
        float dt = 1.0;
        integrationSystem.Update(dt);

        MovementComponent& changedMove = movementManager.Lookup(entity);
        TransformComponent& changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 0.0, 10.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{0.0, 0.0, -1.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, 0.0, -1.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 0.0, 9.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{0.0, 0.0, -2.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, 0.0, -1.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 0.0, 7.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{0.0, 0.0, -3.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, 0.0, -1.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 0.0, 4.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{0.0, 0.0, -4.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, 0.0, -1.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{0.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{0.0, 0.0, -5.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, 0.0, -1.0}));

        PASSED();
    }

    static void IntegrationSystem_Euler_Test_SimpleProjectileMotion_2Dimensions()
    {
        MassManager massManager;
        MovementManager movementManager;
        TransformManager transformManager;
        AccumulatorManager accumulatorManager(&massManager, &transformManager);
        IntegrationSystem_Euler integrationSystem(&accumulatorManager, &massManager, &movementManager, &transformManager);

        // Create the entity and its components.
        Entity entity = EntityManager::CreateEntity();

        AccumulatorComponent accumulatorComponent;
        accumulatorComponent.forceAccumulator_eci = {0.0, 0.0, 0.0};
        accumulatorComponent.torqueAccumulator_eci = {0.0, 0.0, 0.0};

        MassComponent massComponent;
        massComponent.mass = 1.0;
        massComponent.position_cg_eci = {0.0, 10.0, 0.0};
        massComponent.inertiaTensor = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

        MovementComponent moveComponent;
        moveComponent.velocity_eci = {10.0, 0.0, 0.0};
        moveComponent.acceleration_eci = {0.0, -1.0, 0.0}; // Negative acceleration in x-direction only.

        TransformComponent transComponent;
        transComponent.position_eci = {0.0, 10.0, 0.0}; // Positioned 10 units in z-direction only.

        // Add the components to their managers.
        accumulatorManager.Add(entity, accumulatorComponent);
        transformManager.Add(entity, transComponent);
        massManager.Add(entity, massComponent);
        movementManager.Add(entity, moveComponent);

        // Register the entity with the system.
        integrationSystem.RegisterEntity(entity);

        // Update the system.
        float dt = 1.0;
        integrationSystem.Update(dt);

        MovementComponent& changedMove = movementManager.Lookup(entity);
        TransformComponent& changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{10.0, 10.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{10.0, -1.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, -1.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{20.0, 9.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{10.0, -2.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, -1.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{30.0, 7.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{10.0, -3.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, -1.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{40.0, 4.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{10.0, -4.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, -1.0, 0.0}));

        // ===================================================================
        integrationSystem.Update(dt);

        changedMove = movementManager.Lookup(entity);
        changedTrans = transformManager.Lookup(entity);

        ASSERT_TRUE((changedTrans.position_eci == Vector3{50.0, 0.0, 0.0}));
        ASSERT_TRUE((changedMove.velocity_eci == Vector3{10.0, -5.0, 0.0}));
        ASSERT_TRUE((changedMove.acceleration_eci == Vector3{0.0, -1.0, 0.0}));

        PASSED();

    }

    static void IntegrationSystem_Euler_Test_XAxis_PiRotation()
    {
        MassManager massManager;
        MovementManager movementManager;
        TransformManager transformManager;
        AccumulatorManager accumulatorManager(&massManager, &transformManager);
        IntegrationSystem_Euler integrationSystem(&accumulatorManager, &massManager, &movementManager, &transformManager);

        // Create the entity and its components.
        Entity entity = EntityManager::CreateEntity();

        AccumulatorComponent accumulatorComponent;
        accumulatorComponent.forceAccumulator_eci = {0.0, 0.0, 0.0};
        accumulatorComponent.torqueAccumulator_eci = {0.0, 0.0, 0.0}; // << DRIVING FACTOR HERE

        MassComponent massComponent;
        massComponent.mass = 1.0;
        massComponent.position_cg_eci = {0.0, 0.0, 0.0}; // CG position at ECI origin
        massComponent.inertiaTensor = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

        MovementComponent moveComponent;
        moveComponent.velocity_eci = {0.0, 0.0, 0.0};
        moveComponent.acceleration_eci = {0.0, 0.0, 0.0}; // zero linear acceleration
        moveComponent.angular_velocity_eci = {M_PI, 0.0, 0.0};
        moveComponent.angular_acceleration_eci = {0.0, 0.0, 0.0};

        TransformComponent transComponent;
        transComponent.orientation_eci = {0.0, 0.0, 0.0, 0.0};
        transComponent.position_eci = {0.0, 0.0, 0.0}; // Positioned at the ECI origin

        // Add the components to their managers.
        accumulatorManager.Add(entity, accumulatorComponent);
        transformManager.Add(entity, transComponent);
        massManager.Add(entity, massComponent);
        movementManager.Add(entity, moveComponent);

        // Register the entity with the system.
        integrationSystem.RegisterEntity(entity);

        MovementComponent& changedMove = movementManager.Lookup(entity);
        TransformComponent& changedTrans = transformManager.Lookup(entity);
        AccumulatorComponent changedTorque = accumulatorManager.Lookup(entity);     
        Matrix3 rotationMatrix;

        // Update the system.
        float dt = 1.0 / 1000.0;

        // ===================================================================

        // Integrate with dt = 0.1 for 1 second total, to get a full velocity rotation.
        for (int i = 0; i < 1000; ++i)
        {
            integrationSystem.Update(dt);
            MovementComponent& changedMove = movementManager.Lookup(entity);
            TransformComponent& changedTrans = transformManager.Lookup(entity);
            AccumulatorComponent changedTorque = accumulatorManager.Lookup(entity);     
            Matrix3 rotationMatrix;
            rotationMatrix.SetOrientation(changedTrans.orientation_eci);
        }

        EXPECT_NEAR(changedTrans.orientation_eci.w, 0.0, 0.01);
        EXPECT_NEAR(changedTrans.orientation_eci.i, 1.0, 0.01);
        EXPECT_NEAR(changedTrans.orientation_eci.j, 0.0, 0.01);
        EXPECT_NEAR(changedTrans.orientation_eci.k, 0.0, 0.01);
        PASSED();
    }

    static void IntegrationSystem_Euler_Test_YAxis_PiRotation()
    {
        MassManager massManager;
        MovementManager movementManager;
        TransformManager transformManager;
        AccumulatorManager accumulatorManager(&massManager, &transformManager);
        IntegrationSystem_Euler integrationSystem(&accumulatorManager, &massManager, &movementManager, &transformManager);

        // Create the entity and its components.
        Entity entity = EntityManager::CreateEntity();

        AccumulatorComponent accumulatorComponent;
        accumulatorComponent.forceAccumulator_eci = {0.0, 0.0, 0.0};
        accumulatorComponent.torqueAccumulator_eci = {0.0, 0.0, 0.0}; // << DRIVING FACTOR HERE

        MassComponent massComponent;
        massComponent.mass = 1.0;
        massComponent.position_cg_eci = {0.0, 0.0, 0.0}; // CG position at ECI origin
        massComponent.inertiaTensor = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

        MovementComponent moveComponent;
        moveComponent.velocity_eci = {0.0, 0.0, 0.0};
        moveComponent.acceleration_eci = {0.0, 0.0, 0.0}; // zero linear acceleration
        moveComponent.angular_velocity_eci = {0.0, M_PI, 0.0};
        moveComponent.angular_acceleration_eci = {0.0, 0.0, 0.0};

        TransformComponent transComponent;
        transComponent.orientation_eci = {0.0, 0.0, 0.0, 0.0};
        transComponent.position_eci = {0.0, 0.0, 0.0}; // Positioned at the ECI origin

        // Add the components to their managers.
        accumulatorManager.Add(entity, accumulatorComponent);
        transformManager.Add(entity, transComponent);
        massManager.Add(entity, massComponent);
        movementManager.Add(entity, moveComponent);

        // Register the entity with the system.
        integrationSystem.RegisterEntity(entity);

        MovementComponent& changedMove = movementManager.Lookup(entity);
        TransformComponent& changedTrans = transformManager.Lookup(entity);
        AccumulatorComponent changedTorque = accumulatorManager.Lookup(entity);     
        Matrix3 rotationMatrix;

        // Update the system.
        float dt = 1.0 / 1000.0;

        // ===================================================================

        // Integrate with dt = 0.1 for 1 second total, to get a full velocity rotation.
        for (int i = 0; i < 1000; ++i)
        {
            integrationSystem.Update(dt);
            MovementComponent& changedMove = movementManager.Lookup(entity);
            TransformComponent& changedTrans = transformManager.Lookup(entity);
            AccumulatorComponent changedTorque = accumulatorManager.Lookup(entity);     
            Matrix3 rotationMatrix;
            rotationMatrix.SetOrientation(changedTrans.orientation_eci);
        }

        EXPECT_NEAR(changedTrans.orientation_eci.w, 0.0, 0.01);
        EXPECT_NEAR(changedTrans.orientation_eci.i, 0.0, 0.01);
        EXPECT_NEAR(changedTrans.orientation_eci.j, 1.0, 0.01);
        EXPECT_NEAR(changedTrans.orientation_eci.k, 0.0, 0.01);
        PASSED();
    }

    static void IntegrationSystem_Euler_Test_ZAxis_PiRotation()
    {
        MassManager massManager;
        MovementManager movementManager;
        TransformManager transformManager;
        AccumulatorManager accumulatorManager(&massManager, &transformManager);
        IntegrationSystem_Euler integrationSystem(&accumulatorManager, &massManager, &movementManager, &transformManager);

        // Create the entity and its components.
        Entity entity = EntityManager::CreateEntity();

        AccumulatorComponent accumulatorComponent;
        accumulatorComponent.forceAccumulator_eci = {0.0, 0.0, 0.0};
        accumulatorComponent.torqueAccumulator_eci = {0.0, 0.0, 0.0}; // << DRIVING FACTOR HERE

        MassComponent massComponent;
        massComponent.mass = 1.0;
        massComponent.position_cg_eci = {0.0, 0.0, 0.0}; // CG position at ECI origin
        massComponent.inertiaTensor = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

        MovementComponent moveComponent;
        moveComponent.velocity_eci = {0.0, 0.0, 0.0};
        moveComponent.acceleration_eci = {0.0, 0.0, 0.0}; // zero linear acceleration
        moveComponent.angular_velocity_eci = {0.0, 0.0, M_PI};
        moveComponent.angular_acceleration_eci = {0.0, 0.0, 0.0};

        TransformComponent transComponent;
        transComponent.orientation_eci = {0.0, 0.0, 0.0, 0.0};
        transComponent.position_eci = {0.0, 0.0, 0.0}; // Positioned at the ECI origin

        // Add the components to their managers.
        accumulatorManager.Add(entity, accumulatorComponent);
        transformManager.Add(entity, transComponent);
        massManager.Add(entity, massComponent);
        movementManager.Add(entity, moveComponent);

        // Register the entity with the system.
        integrationSystem.RegisterEntity(entity);

        MovementComponent& changedMove = movementManager.Lookup(entity);
        TransformComponent& changedTrans = transformManager.Lookup(entity);
        AccumulatorComponent changedTorque = accumulatorManager.Lookup(entity);     
        Matrix3 rotationMatrix;

        // Update the system.
        float dt = 1.0 / 1000.0;

        // ===================================================================

        // Integrate with dt = 0.1 for 1 second total, to get a full velocity rotation.
        for (int i = 0; i < 1000; ++i)
        {
            integrationSystem.Update(dt);
            MovementComponent& changedMove = movementManager.Lookup(entity);
            TransformComponent& changedTrans = transformManager.Lookup(entity);
            AccumulatorComponent changedTorque = accumulatorManager.Lookup(entity);     
            Matrix3 rotationMatrix;
            rotationMatrix.SetOrientation(changedTrans.orientation_eci);
        }

        EXPECT_NEAR(changedTrans.orientation_eci.w, 0.0, 0.01);
        EXPECT_NEAR(changedTrans.orientation_eci.i, 0.0, 0.01);
        EXPECT_NEAR(changedTrans.orientation_eci.j, 0.0, 0.01);
        EXPECT_NEAR(changedTrans.orientation_eci.k, 1.0, 0.01);
        PASSED();
    }
};

#endif //MOTION_SYSTEM_TESTS_H