/*!
 * \file	LED.h
 *
 * \date	Sep 14, 2016
 * \author	Alex Kempster
 *
 * \brief
 * header file for LED.c
 *
 * This module is used to control LED's on any connected IO line. A list of
 * known LED's is included in this file but any GPIO line can be passed to this
 * module to interface to an LED.
 */

#ifndef INC_LED_H_
#define INC_LED_H_

/* Library include files */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

/* Project include files */
#include "platformConfiguration.h"


#ifdef STM32F429NUCLEO

#define LED_PIN_NUCLEO_GREEN 	(GPIO_PIN_0)
#define LED_PORT_NUCLEO_GREEN	(GPIOB)

#define LED_NUCLEO_BLUE			(GPIO_PIN_7)
#define LED_PORT_NUCLEO_BLUE	(GPIOB)

#define LED_NUCLEO_RED			(GPIO_PIN_14)
#define LED_PORT_NUCLEO_RED 	(GPIOB)

typedef enum
{
	LED_ON_HIGH = 0,
	LED_ON_LOW,
	LED_OFF_HIGH,
	LED_OFF_LOW
}LED_drive;

typedef struct
{
	GPIO_TypeDef* 	port;		// port to interface with (e.g. GPIOA)
	uint16_t 		pins;		// pins to use (can be OR'd together) (e.g. GPIO_PIN_0)
	uint8_t 		pull;		// GPIO_NOPULL | GPIO_PULLUP | GPIO_PULLDOWN
} LED_Config;

#endif

/* Function prototype declarations */
void LED_Init(LED_Config config);
void LED_Set(LED_Config config, LED_drive state);

#endif /* INC_LED_H_ */
