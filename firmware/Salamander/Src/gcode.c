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
			case GCODE_FILESYSTEM_LIST_CUR_DIR:
				break;
			case GCODE_FILESYSTEM_MOUNT:
				break;
			case GCODE_FILESYSTEM_UNMOUNT:
				break;
			case GCODE_FILESYSTEM_FILE_SELECT:
				break;
			case GCODE_PRINT_START_RESUME:
				break;
			case GCODE_PRINT_PAUSE:
				break;
			case GCODE_FILE_SET_POSITION_BYTES:
				break;
			case GCODE_PRINT_REPORT_STATUS:
				break;
			case GCODE_FILESYSTEM_WRITE_FILE:
				break;
			case GCODE_FILESYSTEM_STOP_WRITE_FILE:
				break;
			case GCODE_PRINT_EJECT:
				break;
			case GCODE_LOOP_PROGRAM:
				break;
			case GCODE_STOP_IF_NO_MATERIAL:
				break;
			case GCODE_STOP_IF_NO_MATERIAL_HEATBED_ON:
				break;
			case GCODE_POWER_SUPPLY_ON:
				break;
			case GCODE_POWER_SUPPLY_OFF:
				break;
			case GCODE_STOP_IDLE_HOLD:
				break;
			case GCODE_SET_STEPS_PER_UNIT:
				break;
			case GCODE_EXTRUDER_1_FORWARD:
				break;
			case GCODE_EXTRUDER_1_REVERSE:
				break;
			case GCODE_EXTRUDER_TURN_ALL_OFF:
				break;
			case GCODE_EXTRUDER_SET_TEMPERATURE:
				break;
			case GCODE_EXTRUDER_GET_TEMPERATURE:
				break;
			case GCODE_FAN_SET_SPEED:
				break;
			case GCODE_FAN_OFF:
				break;
			case GCODE_EXTRUDER_SET_SPEED:
				break;
			case GCODE_EXTRUDER_SET_TEMPERATURE_WAITING:
				break;
			case GCDOE_SET_CURRENT_LINE_NUMBER:
				break;
			case GCODE_SET_DEBUG_LEVEL:
				break;
			case GCODE_STOP_EMERGENCY:
				break;
			case GCODE_EXTRUDER_SET_PWM:
				break;
			case GCODE_GET_CURRENT_POSITION:
				break;
			case GCODE_GET_FIRMWARE_VERSION:
				break;
			case GCODE_WAIT_FOR_ALL_TEMPERATURES:
				break;
			case GCODE_GET_ZERO_POSITION_IN_STEPS:
				break;
			case GCODE_GET_STATUS_ENDSTOPS:
				break;
			case GCODE_EXTRUDER_VALVE_OPEN:
				break;
			case GCODE_EXTRUDER_VALVE_CLOSE:
				break;
			case GCODE_EXTRUDER_PRESSURE_SET:
				break;
			case GCODE_EXTRUDER_PRESSURE_OFF:
				break;
			case GCODE_HEATED_BED_SET_TEMPERATURE:
				break;
			case GCODE_HEATED_CHAMBER_SET_TEMPERATURE:
				break;
			case GCODE_SET_HOLDING_PRESSURE:
				break;
			case GCODE_SET_HOTEND_MAX_TEMPERATURE:
				break;
			case GCODE_SET_EXTRUDER_MATERIALS_COUNT:
				break;
			case GCODE_SET_OFFSET_Z:
				break;
			case GCODE_AUTO_REVERSE_AND_PRIME_DISABLE:
				break;
			case GCODE_AUTO_REVERSE_AND_PRIME_ENABLE:
				break;
			case GCODE_WAIT_FOR_TEMPERATURE_SET:
				break;
			case GCODE_CONVERYOR_BELT_START:
				break;
			case GCODE_CONVEYOR_BELT_STOP:
				break;
			case GCODE_COOLER_FAN_START:
				break;
			case GCODE_COOLER_FAN_STOP:
				break;
			case GCODE_GENERATE_BEEP:	// beep with s hz for p milliseconds

			default:
				/// \todo missing code
				break;
		}
	} else
	{
		// should never get here
	}
}

