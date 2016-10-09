/*!
 * \file	parsing.c
 *
 * \date	Oct 9, 2016
 * \author	Alex
 *
 * \brief
 */

/* Standard include files */
#include <stdint.h>

/* Project Includes */
#include "usbd_cdc_if.h"

#include "gcode.h"
#include "parsing.h"
#include "usbComms.h"

#define PARSING_MAX_LINE_LEN	(32u)

bool PARSING_GCODE(uint8_t *string, uint8_t len);

void PARSING_HandleUsbComms(void)
{
	static uint8_t line[PARSING_MAX_LINE_LEN] = "";
	static uint8_t idx = 0;

	uint8_t byte;


	// attempt to read from com port
	byte = USB_COMMS_ReadByte();

	if (byte != '\0')	// valid byte received
	{
		line[idx] = byte;	// store in local line
		idx++;				// and position for next go around

		if ((byte == '\r') || (byte == '\n'))	// line end reached
		{
			// pass the line around to see if it makes sense to any module
			PARSING_GCODE(line, idx);

			// reset the line
			for (uint8_t i = 0; i < PARSING_MAX_LINE_LEN; i++)
			{
				line[i] = '\0';
			}
			idx = 0;
		}

		CDC_Transmit_FS(&byte, 1);
	}
}

bool PARSING_GCODE(uint8_t *string, uint8_t len)
{
	bool retval = false;

	if ((string[0] == 'M') ||	// potential Mxxx code
		(string[0] == 'm'))
	{
		uint8_t mStr[] = "Potential M command\n";
		CDC_Transmit_FS(mStr, sizeof(mStr));
	} else if ((string[0] == 'G') ||	// potential Gxxx code
			   (string[0] == 'g'))
	{
		uint8_t gStr[] = "Potential G command\n";
		CDC_Transmit_FS(gStr, sizeof(gStr));
	} else
	{
		uint8_t errStr[] = "Not a GCODE\n";
		CDC_Transmit_FS(errStr, sizeof(errStr));
	}

	return retval;
}
