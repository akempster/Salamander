/*!
 * \file	testMain.c
 *
 * \date	Aug 20, 2017
 * \author	Alex
 *
 * \brief
 */

/* Include files */
#include "testMain.h"

#include "unity_fixture.h"

void RunAllTests(void);

void TestMain(void)
{
	const char *testParams[] = {"", "-v"};

	uint8_t mStr[] = "freedom\r\n";
	while (0 != CDC_Transmit_FS(mStr, sizeof(mStr)));

	UnityMain(2, testParams, RunAllTests);
}


void RunAllTests(void)
{
	RUN_TEST_GROUP(motor);
}
