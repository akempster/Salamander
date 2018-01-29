/*!
 * \file	motor.h
 *
 * \date	Oct 16, 2016
 * \author	Alex
 *
 * \brief
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "stm32F4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

typedef enum
{
	CLOCKWISE = 0,
	ANTICLOCKWISE
}STEPPER_DIRECTION;

typedef struct
{
	GPIO_TypeDef *port;
	uint32_t Pin;
} GPIO_PIN;

typedef struct
{
		GPIO_PIN direction;
		GPIO_PIN step;
}DRV8825;

void DRV8825_Step(DRV8825 *motor);
void DRV8825_SetDirection(DRV8825 *motor, STEPPER_DIRECTION dir);

#endif /* MOTOR_H_ */
