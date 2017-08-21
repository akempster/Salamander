/*!
 * \file	testMain.c
 *
 * \date	Aug 20, 2017
 * \author	Alex
 *
 * \brief
 */

/* Include files */
#include "unity_fixture.h"

void RunAllTests(void);

void TestMain(void)
{
	const char *testParams[] = {"", "-v"};

	UnityMain(2, testParams, RunAllTests);
}


void RunAllTests(void)
{

}
