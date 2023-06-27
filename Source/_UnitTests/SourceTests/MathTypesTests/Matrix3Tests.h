#ifndef MATRIX3_TESTS_H
#define MATRIX3_TESTS_H

#include "../../_Utilities/_Utilities.h"
#include "../../../MathTypes/Matrix3.h"

class Matrix3Tests
{
    public:

    static void SwapXYDirections()
    {
        // Create a basis matrix where the y and z directions are swapped.
        Matrix3 yxz_basis{0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0};
        Vector3 xyz_vector{1.0, 2.0, 3.0};

        // Rotate the vector.
        auto result = yxz_basis * xyz_vector;

        // Make sure the y and z directions have been swapped.
        ASSERT_TRUE(result.x == 2.0);
        ASSERT_TRUE(result.y == 1.0);
        ASSERT_TRUE(result.z == 3.0);
        PASSED();
    }

    static void SwapXZDirections()
    {
        // Create a basis matrix where the y and z directions are swapped.
        Matrix3 zyx_basis{0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0};
        Vector3 xyz_vector{1.0, 2.0, 3.0};

        // Rotate the vector.
        auto result = zyx_basis * xyz_vector;

        // Make sure the y and z directions have been swapped.
        ASSERT_TRUE(result.x == 3.0);
        ASSERT_TRUE(result.y == 2.0);
        ASSERT_TRUE(result.z == 1.0);
        PASSED();
    }

    static void SwapYZDirections()
    {
        // Create a basis matrix where the y and z directions are swapped.
        Matrix3 xzy_basis{1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0};
        Vector3 xyz_vector{1.0, 2.0, 3.0};

        // Rotate the vector.
        auto result = xzy_basis * xyz_vector;

        // Make sure the y and z directions have been swapped.
        ASSERT_TRUE(result.x == 1.0);
        ASSERT_TRUE(result.y == 3.0);
        ASSERT_TRUE(result.z == 2.0);
        PASSED();
    }
};

#endif //MATRIX3_TESTS_H