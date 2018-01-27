/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
typedef struct
{
	GPIO_TypeDef *port;
	uint32_t Pin;
	uint32_t Mode;
	uint32_t Pull;
	uint32_t Speed;
	uint32_t Alternate;

} GPIO_CONFIG;

GPIO_CONFIG gpioTable[] =
{
	// PORT	PIN				MODE					PULL			SPEED					Alternate
	{GPIOC, GPIO_PIN_13, 	GPIO_MODE_INPUT, 		GPIO_NOPULL, 	GPIO_SPEED_FREQ_LOW, 	0},			// user blue button (dev board)
	{GPIOC, GPIO_PIN_0,		GPIO_MODE_OUTPUT_PP,	GPIO_NOPULL,	GPIO_SPEED_FREQ_LOW,	0},			// STEP motor0 pin - may need to remove internal pull-down

	{GPIOE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|
			GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|
			GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0|
			GPIO_PIN_1,		GPIO_MODE_ANALOG,		GPIO_NOPULL, 	GPIO_SPEED_FREQ_LOW,	0},			// PORTE unused pins

	{GPIOF, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|
			GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|
			GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_MODE_ANALOG,	GPIO_NOPULL, GPIO_SPEED_FREQ_LOW,	0},	// PORTF unused pins

	{GPIOC, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6 |GPIO_PIN_7,
							GPIO_MODE_ANALOG,		GPIO_NOPULL,	GPIO_SPEED_FREQ_LOW,	0},			// PORTC unused pins

	{GPIOA, GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_15,	GPIO_MODE_ANALOG,	GPIO_NOPULL,	GPIO_SPEED_FREQ_LOW,	0},	//PORTA unused pins

	{GPIOB,	GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                    |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15|GPIO_PIN_3
                    |GPIO_PIN_4|GPIO_PIN_8,		GPIO_MODE_ANALOG,	GPIO_NOPULL,	GPIO_SPEED_FREQ_LOW,	0},	// PORTB unused pins

    {GPIOG, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                    |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_9
                    |GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_15, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0},	// PORTG unused pins

    {GPIOB, LD3_Pin|LD2_Pin,	GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0},
    {GPIOD, STLK_RX_Pin|STLK_TX_Pin, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART3},
    {GPIOD, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                    |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4
                    |GPIO_PIN_6|GPIO_PIN_7, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0},	// GPIOD unused pins
     {USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin,GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,   GPIO_SPEED_FREQ_LOW, 0},
     {USB_OverCurrent_GPIO_Port,USB_OverCurrent_Pin, GPIO_MODE_INPUT,GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0},

};

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through 
        * the Code Generation settings)
     PD8   ------> USART3_TX
     PD9   ------> USART3_RX
*/
void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*
     * Configure all pins as listed in the gpioTable
     */
    const uint8_t tableSize = sizeof(gpioTable)/sizeof(gpioTable[0]);
    for (uint8_t i = 0; i < tableSize; i++)
    {
  	  // setup structure based on table contents
    	  GPIO_InitStruct.Pin 		= gpioTable[i].Pin;
    	  GPIO_InitStruct.Mode 		= gpioTable[i].Mode;
    	  GPIO_InitStruct.Pull		= gpioTable[i].Pull;
    	  GPIO_InitStruct.Speed		= gpioTable[i].Speed;
    	  GPIO_InitStruct.Alternate	= gpioTable[i].Alternate;

    	  // This line configures the pin to the settings in gpioTable
    	  HAL_GPIO_Init(gpioTable[i].port, &GPIO_InitStruct);
    }


    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
