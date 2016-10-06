/*!
 * \file	usbComms.c
 *
 * \date	Oct 6, 2016
 * \author	Alex Kempster
 *
 * \brief
 */

/* Standard include files */
#include <stdbool.h>

/* Project include files */
#include "usbComms.h"

/* Module variables */
circularBuffer receivedData;

/*!
 * Initialise the USB comms interface:
 * 1. set the default state of the receive buffer
 */
void USB_COMMS_Init (void)
{
	/* Initialise receive buffer */
	receivedData.readIdx = 0;
	receivedData.writeIdx = 0;

	for (uint8_t i = 0; i < USB_COMMS_RX_BUF_LEN; i++)
	{
		receivedData.data[i] = 0;
	}
}

/*!
 * Adds a character to the receive buffer (i.e. data from the USB host)
 *
 * \param c		the character to add to the buffer
 *
 * \retval true		error occurred
 * \retval false	no error
 */
bool USB_COMMS_AddToRxBuffer(uint8_t c)
{
	bool retval = false;

	// write the data to the next available location
	receivedData.data[receivedData.writeIdx] = c;

	// If at the end of the array
	if ((receivedData.writeIdx+1) == USB_COMMS_RX_BUF_LEN)
	{
		// at the end of the array, wrap to start
		receivedData.writeIdx = 0;
	}
	else
	{
		// not going to wrap yet, safe to increment index to the next space
		receivedData.writeIdx++;
	}

	// Now we need to check if the write location has caught the read location
	if(receivedData.readIdx == receivedData.writeIdx)
	{
		// they have caught each other, so need to move back a space
		if (receivedData.writeIdx == 0)	// wrap back under
		{
			receivedData.writeIdx = USB_COMMS_RX_BUF_LEN-1;
		}
		else
		{
			// no wrap so safe to decrement
			receivedData.writeIdx--;
		}

	}

	return (retval);
}

/*
 * Reads a character from the receive buffer, equivalent to getchar.
 *
 * This function is non-blocking.
 *
 * \retval 	the character from the receive buffer, if no data is available then
 * 			the '\0' character shall be returned.
 */
uint8_t USB_COMMS_ReadByte(void)
{
	uint8_t byte = '\0';

	// if data to read
	if (receivedData.readIdx != receivedData.writeIdx)
	{
		byte = receivedData.data[receivedData.readIdx];		// get the data

		receivedData.readIdx++;		// move to next byte in buffer

		// check for wrap around
		if (receivedData.readIdx == USB_COMMS_RX_BUF_LEN)
		{
			receivedData.readIdx = 0;
		}
	}

	return byte;
}
