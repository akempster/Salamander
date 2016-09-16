/*
 * gcode.c
 *
 *  Created on: 16 Sep 2016
 *      Author: Alex
 */

#include "gcode.h"

void GCODE_process(GCODE command)
{
	if ((command.type == 'g') ||
		(command.type == 'G'))
	{
		switch(command.number)
		{
			case GCODE_MOVEMENT_RAPID:
				break;
			case GCODE_MOVEMENT_CONTROLLED:
				break;
			case GCODE_WAIT:
				break;
			case GCODE_SET_UNITS_INCH:
				break;
			case GCODE_SET_UNITS_MM:
				break;
			case GCODE_HOME:
				break;
			case GCODE_POSITIONING_ABSOLUTE:
				break;
			case GCODE_POSITIONING_RELATIVE:
				break;
			case GCODE_SET_POSITION:
				break;
			default:
				/// \todo missing code
				break;
		}
	}
	else if ((command.type == 'm') ||
			 (command.type == 'M'))
	{
		switch(command.number)
		{
			case GCODE_STOP_WHEN_READY:
				break;
			case GCODE_MOTORS_ENABLE:
				break;
			case GCODE_MOTORS_DISABLE:
				break;
			case 20:	// list files at the root folder of the SD card
				break;
			case GCODE_FILESYSTEM_MOUNT:
				break;
			case GCODE_FILESYSTEM_UNMOUNT:
				break;
			case 23:	// Select file for printing
				break;
			case 24:	// start/resume SD card print
				break;
			case GCODE_PRINT_PAUSE:
				break;
			case 26:	// Set SD position in bytes
				break;
			case 27:	// report SD print status
				break;
			case 28:	// write program to SD card
				break;
			case 29:	// stop writing program to SD card
				break;
			case GCODE_PRINT_EJECT:
				break;
			case 41:	// loop program (stop with reset button)
				break;
			case 42:	// stop if out of material
				break;
			case 43:	// stop if out of material but leave heated bed on
				break;
			case 80:	// turn on ATX power supply
				break;
			case 81:	// turn off ATX power supply
				break;
			case 84:	// Stop idle hold (do not use whilst printing)
				break;
			case 92:	// program set steps per unit
				break;
			case 101:	// set extruder 1 to forward (outdated)
				break;
			case 102:	// set extruder 1 to reverse (outdated)
				break;
			case 103:	// turn all extruders off (outdated)
				break;
			case 104:	// set extruder temperature (not waiting)
				break;
			case 105:	// get extruder temperature
				break;
			case GCODE_FAN_SET_SPEED:
				break;
			case GCODE_FAN_OFF:
				break;
			case 108:	// set extruder speed (outdated)
				break;
			case 109:	// set extruder temperature (wait untill reached)
				break;
			case 110:	// set current line number
				break;
			case GCODE_SET_DEBUG_LEVEL:
				break;
			case GCODE_STOP_EMERGENCY:
				break;
			case 113:	// set extruder pwm to x
				break;
			case GCODE_GET_CURRENT_POSITION:
				break;
			case 115:	// get firmware version and capabilities
				break;
			case 116:	// wait for all temperatures
				break;
			case 117:	// get zero position in steps
				break;
			case 119:	// get endstop status
				break;
			case GCODE_EXTRUDER_VALVE_OPEN:
				break;
			case GCODE_EXTRUDER_VALVE_CLOSE:
				break;
			case GCODE_EXTRUDER_PRESSURE_SET:
				break;
			case GCODE_EXTRUDE_PRESSURE_OFF:
				break;
			case GCODE_HEATED_BED_SET_TEMPERATURE:
				break;
			case GCODE_HEATED_CHAMBER_SET_TEMPERATURE:
				break;
			case 142:	// Set holding pressure
				break;
			case 143:	// set maximum hot-end temperature
				break;
			case 160:	// set number of materials an extruder can handle
				break;
			case 203:	// set z offset
				break;
			case 226:	// pauses printing
				break;
			case 227:	// enable automatic reverse and prime
				break;
			case 228:	// disable automatic reverse and prime
				break;
			case 229:	// enable automatic reverse and prime
				break;
			case 230:	// enable / disable wait for temp
				break;
			case 240:	// start conveyor belt motor
				break;
			case 241:	// stop conveyor belt motor
				break;
			case 245:	// start cooler fan
				break;
			case 246:	// stop cooler fan
				break;
			case 300:	// beep with s hz for p milliseconds

			default:
				/// \todo missing code
				break;
		}
	} else
	{
		// should never get here
	}
}

