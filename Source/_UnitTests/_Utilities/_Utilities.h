#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <stdexcept>
#include <string>

#define TEST_FUNCTION(function) function;

#define THROW() throw(std::runtime_error(__FUNCTION__))

#define ASSERT_TRUE(val) if (!val) THROW()
#define PASSED() std::cout << __FUNCTION__ << " passed!" << std::endl;

#define EXPECT_NEAR(val, targetVal, tolerance) if(!(abs(targetVal - val) < tolerance)) THROW()

#endif //_UTILITIES_H