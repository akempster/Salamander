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
	uint32_t Pin;
	GPIO_TypeDef port;
} GPIO_PIN;

typedef struct
{
		GPIO_PIN direction;
		GPIO_PIN step;
}DRV8825;

#endif /* MOTOR_H_ */
