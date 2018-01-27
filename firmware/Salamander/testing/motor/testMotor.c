/*!
 * \file	testMotor.c
 *
 * \date	Aug 21, 2017
 * \author	Alex
 *
 * \brief
 */


#include "unity_fixture.h"

TEST_GROUP(motor);

TEST_SETUP(motor)
{
	// nothing to do
}

TEST_TEAR_DOWN(motor)
{
	// nothing to do
}

TEST(motor, CanControlMotorsEnabledVariable)
{
	TEST_FAIL();
}

TEST_GROUP_RUNNER(motor)
{
	RUN_TEST_CASE(motor, CanControlMotorsEnabledVariable);
}
