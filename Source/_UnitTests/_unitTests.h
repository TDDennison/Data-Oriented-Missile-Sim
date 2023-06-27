#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include "SourceTests/HelperMethodsTests.h"

#include "SourceTests/MathTypesTests/Matrix3Tests.h"
#include "SourceTests/SystemsTests/IntegrationSystem_EulerTests.h"

class UnitTests
{
    public:

    static void RunAllTests()
    {
        TEST_FUNCTION(HelperMethodsTests::CalculateDistanceTest_DistanceAlongXAxisOnly());
        TEST_FUNCTION(HelperMethodsTests::CalculateDistanceTest_DistanceAlongYAxisOnly());
        TEST_FUNCTION(HelperMethodsTests::CalculateDistanceTest_DistanceAlongZAxisOnly());
        TEST_FUNCTION(HelperMethodsTests::CalculateDistanceTest_PointsAreTheSame());
        TEST_FUNCTION(HelperMethodsTests::CalculateDistanceTest_PointsNotAtOrigin());
        TEST_FUNCTION(HelperMethodsTests::CalculateDistanceTest_345Triangle());

        TEST_FUNCTION(IntegrationSystem_Euler_Tests::IntegrationSystem_Euler_Test_BasicFallingObject_XDirection());
        TEST_FUNCTION(IntegrationSystem_Euler_Tests::IntegrationSystem_Euler_Test_BasicFallingObject_YDirection());
        TEST_FUNCTION(IntegrationSystem_Euler_Tests::IntegrationSystem_Euler_Test_BasicFallingObject_ZDirection());
        TEST_FUNCTION(IntegrationSystem_Euler_Tests::IntegrationSystem_Euler_Test_SimpleProjectileMotion_2Dimensions());
        TEST_FUNCTION(IntegrationSystem_Euler_Tests::IntegrationSystem_Euler_Test_XAxis_PiRotation());
        TEST_FUNCTION(IntegrationSystem_Euler_Tests::IntegrationSystem_Euler_Test_YAxis_PiRotation());
        TEST_FUNCTION(IntegrationSystem_Euler_Tests::IntegrationSystem_Euler_Test_ZAxis_PiRotation());

        TEST_FUNCTION(Matrix3Tests::SwapXYDirections());
        TEST_FUNCTION(Matrix3Tests::SwapXZDirections());
        TEST_FUNCTION(Matrix3Tests::SwapYZDirections());
    }
};

#endif //UNIT_TESTS_H