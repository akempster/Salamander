/*!
 * \file	motor.c
 *
 * \date	Oct 16, 2016
 * \author	Alex
 *
 * \brief
 */

/* Include files */
#include <stdbool.h>
#include "motor.h"

/* Global variables */
bool motorsEnabled = true;

/*!
 * MOTOR_STEPPER_SetDirection
 *
 * Sets the direction of the stepper motor
 *
 * \param stepper motor to control
 * \param direction	(clockwise | anticlockwise)
 */
void DRV8825_SetDirection(DRV8825 *motor, STEPPER_DIRECTION dir)
{
	if (dir == CLOCKWISE)
	{
#warning missing code
	}
	else
	{
#warning missing code
	}
}
