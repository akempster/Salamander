/*!
 * \file	motor.c
 *
 * \date	Oct 16, 2016
 * \author	Alex
 *
 * \brief
 */

/* Include files */
#include "stm32f4xx_hal.h"

#include <stdbool.h>
#include "motor.h"
#include "gpio.h"

/* Global variables */
bool motorsEnabled = true;

/*!
 * DRV8825_SetDirection
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
		HAL_GPIO_WritePin(motor->direction.port, motor->direction.Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(motor->direction.port, motor->direction.Pin, GPIO_PIN_RESET);
	}
}

/*!
 * DRV8825_Step
 *
 * Moves the stepper motor by one step
 *
 * \param motor		stepper motor to control
 */
void DRV8825_Step(DRV8825 *motor)
{
	/* DRV8825
	 * Step frequency max: 250kHz
	 * Pulse duration, STEP low/high: 1.9uS
	 */
	HAL_GPIO_WritePin(motor->step.port, motor->step.Pin, GPIO_PIN_SET);

#warning need to fix a proper delay
	HAL_Delay(1);

	HAL_GPIO_WritePin(motor->step.port, motor->step.Pin, GPIO_PIN_RESET);

	HAL_Delay(1);
}
