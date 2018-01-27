/*!
 * \file	LED.c
 *
 * \date	Sep 14, 2016
 * \author	Alex
 *
 * \brief
 */

/* Library include files */
#include <stdbool.h>

/* Project include files */
#include "LED.h"

/* Interface functions */

/*!
 * \brief
 * Initialise a GPIO line to be used as an LED output
 *
 * \param port	the port which the pin(s) reside
 * \param pins	the pin(s) to set for LED's, if they are on the same port
 * 				then the pins can be configured simultaneously.
 */
void LED_Init(LED_Config config)
{
	GPIO_InitTypeDef init;

	init.Mode = GPIO_MODE_OUTPUT_PP;
	init.Pin = config.pins;
	init.Pull = config.pull;
	init.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(config.port, &init);

}

/*!
 * \brief
 * turns an LED on or off. use the LED_drive to determine if the LED should be
 * on or off. The HIGH LOW part of the enum indicates if the LED is active
 * high or active low.
 *
 * \param port	the port which the pin resides
 * \param pin	the pin to turn on/off
 * \param state	which state to turn the LED and how the LED is driven
 */
void LED_Set(LED_Config config, LED_drive state)
{
	// if need to drive an output logic 1
	if ((state == LED_ON_HIGH) || (state == LED_OFF_HIGH))
	{
		HAL_GPIO_WritePin(config.port, config.pins, GPIO_PIN_SET);
	} else	// output logic 0
	{
		HAL_GPIO_WritePin(config.port, config.pins, GPIO_PIN_RESET);
	}
}

/* Module functions */
