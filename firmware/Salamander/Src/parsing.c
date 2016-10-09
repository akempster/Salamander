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

	GCODE currentCommand;

	if ((string[0] == 'M') ||	// potential Mxxx code
		(string[0] == 'm'))
	{
		// convert gcode instruction type, ignore parameters for now.
		currentCommand.type = 'M';
		currentCommand.number = (uint16_t) strtol((char*)(string+1), 			// skip 'M' character
		                                          NULL,
		                                          10);							// base in denary

		/// \todo	handle instruction parameters! (add in to currentCommand struct)

		/* process the command
		 * - this is an array of function pointers
		 * - the array index matches the gcode number
		 * - this array is specifically for M series gcode instructions
		 * - do not overshoot the array, thus the check on size.
		 * 	 overshooting would cause undefined behaviour and program failure.
		 */
		if (currentCommand.number > 300)	// erroneous command
		{

			mCommands[301](&currentCommand);
		} else
		{	// valid command, process
			mCommands[currentCommand.number](&currentCommand);
		}

		retval = true;

		uint8_t mStr[] = "Potential M command\r\n";
		CDC_Transmit_FS(mStr, sizeof(mStr));
	} else if ((string[0] == 'G') ||	// potential Gxxx code
			   (string[0] == 'g'))
	{
		uint8_t gStr[] = "Potential G command\r\n";
		CDC_Transmit_FS(gStr, sizeof(gStr));
	} else
	{
		uint8_t errStr[] = "Not a GCODE\r\n";
		CDC_Transmit_FS(errStr, sizeof(errStr));
	}

	return (retval);
}
