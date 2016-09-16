/*
 * gcode.h
 *
 *  Created on: 16 Sep 2016
 *      Author: Alex
 */

#ifndef INC_GCODE_H_
#define INC_GCODE_H_

enum
{
	GCODE_RAPID_MOVEMENT = 0,
}GCODE_general;

typedef struct
{
	char 	type;		// 'G' or 'M' code
	uint8_t	number;		// command number
}GCODE;



#endif /* INC_GCODE_H_ */
