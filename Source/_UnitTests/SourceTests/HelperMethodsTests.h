#ifndef HELPER_METHODS_TESTS_H
#define HELPER_METHODS_TESTS_H

#include "../_Utilities/_Utilities.h"

#include "../../HelperMethods.h"
#include "../../Utilities.h"

class HelperMethodsTests
{
    public:

    static void CalculateDistanceTest_PointsAreTheSame()
    {
        Vector3 a{0.0, 0.0, 0.0};
        Vector3 b{0.0, 0.0, 0.0};

        float distance = HelperMethods::CalculateDistance(a, b);

        ASSERT_TRUE((distance == 0.0));
        PASSED();
    }    

    static void CalculateDistanceTest_DistanceAlongXAxisOnly()
    {
        Vector3 a{10.0, 0.0, 0.0};
        Vector3 b{0.0, 0.0, 0.0};

        float distance = HelperMethods::CalculateDistance(a, b);

        ASSERT_TRUE((distance == 10.0));
        PASSED();
    }

    static void CalculateDistanceTest_DistanceAlongYAxisOnly()
    {
        Vector3 a{0.0, 10.0, 0.0};
        Vector3 b{0.0, 0.0, 0.0};

        float distance = HelperMethods::CalculateDistance(a, b);

        ASSERT_TRUE((distance == 10.0));
        PASSED();
    }

    static void CalculateDistanceTest_DistanceAlongZAxisOnly()
    {
        Vector3 a{0.0, 0.0, 10.0};
        Vector3 b{0.0, 0.0, 0.0};

        float distance = HelperMethods::CalculateDistance(a, b);

        ASSERT_TRUE((distance == 10.0));
        PASSED();
    }

    static void CalculateDistanceTest_345Triangle()
    {
        Vector3 a{3.0, 4.0, 0.0};
        Vector3 b{0.0, 0.0, 0.0};

        float distance = HelperMethods::CalculateDistance(a, b);

        ASSERT_TRUE((distance == 5.0));
        PASSED();
    }

    static void CalculateDistanceTest_PointsNotAtOrigin()
    {
        Vector3 a{1000000.0, 0.0, 0.0};
        Vector3 b{2000000.0, 0.0, 0.0};

        float distance = HelperMethods::CalculateDistance(a, b);

        ASSERT_TRUE((distance == 1000000.0));
        PASSED();
    }
    
};

#endif //HELPER_METHODS_TESTS_H