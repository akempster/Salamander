/*!
 * \file	usbComms.h
 *
 * \date	Oct 6, 2016
 * \author	Alex
 *
 * \brief
 */

#ifndef USBCOMMS_H_
#define USBCOMMS_H_

/* Standard include files */
#include <stdint.h>
#include <stdbool.h>

/* Macros and definitions */
#define USB_COMMS_RX_BUF_LEN	(64u)

/* Structures and unions */
typedef struct
{
		uint8_t data[USB_COMMS_RX_BUF_LEN];
		uint8_t readIdx;
		uint8_t writeIdx;
} circularBuffer;

/* Function prototype declarations */
void USB_COMMS_Init (void);

// add a character to the receive buffer
bool USB_COMMS_AddToRxBuffer(uint8_t c);

// reads a byte from the receive buffer, returns '\0' if no data to read
uint8_t USB_COMMS_ReadByte(void);

// read a '\r' or '\n' terminated string from the receive buffer
int16_t USB_COMMS_ReadLine(uint8_t *str, uint8_t len);

#endif /* USBCOMMS_H_ */
