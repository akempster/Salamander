/*
 * gcode.c
 *
 *  Created on: 16 Sep 2016
 *      Author: Alex
 */

#include <stdbool.h>

#include "gcode.h"
#include "usbd_cdc_if.h"

extern bool motorsEnabled;	// currently declared in main.c, will need to refactor

bool GCODE_UnhandledCommand(GCODE *command);
bool GCODE_MotorsEnableCommand(GCODE *command);
bool GCODE_MotorsDisableCommand(GCODE *command);

/* This is an array of funtion pointers used to jump to a handler for a
 * specific gcode command, this array deals specifically with M type commands
 */
gcode_function_type mCommands[] =
{
    GCODE_UnhandledCommand,	// 0
    GCODE_UnhandledCommand,	// 1
    GCODE_UnhandledCommand,	// 2
    GCODE_UnhandledCommand,	// 3
    GCODE_UnhandledCommand,	// 4
    GCODE_UnhandledCommand,	// 5
    GCODE_UnhandledCommand,	// 6
    GCODE_UnhandledCommand,	// 7
    GCODE_UnhandledCommand,	// 8
    GCODE_UnhandledCommand,	// 9
    GCODE_UnhandledCommand,	// 10
    GCODE_UnhandledCommand,	// 11
    GCODE_UnhandledCommand,	// 12
    GCODE_UnhandledCommand,	// 13
    GCODE_UnhandledCommand,	// 14
    GCODE_UnhandledCommand, // 15
    GCODE_UnhandledCommand,	// 16
    GCODE_MotorsEnableCommand,		// M17
    GCODE_MotorsDisableCommand,		// M18
    GCODE_UnhandledCommand,	// 18
    GCODE_UnhandledCommand,	// 19
    GCODE_UnhandledCommand,	// 20
    GCODE_UnhandledCommand,	// 21
    GCODE_UnhandledCommand,	// 22
    GCODE_UnhandledCommand,	// 23
    GCODE_UnhandledCommand,	// 24
    GCODE_UnhandledCommand,	// 25
    GCODE_UnhandledCommand,	// 26
    GCODE_UnhandledCommand,	// 27
    GCODE_UnhandledCommand,	// 28
    GCODE_UnhandledCommand,	// 29
    GCODE_UnhandledCommand,	// 30
    GCODE_UnhandledCommand,	// 31
    GCODE_UnhandledCommand,	// 32
    GCODE_UnhandledCommand,	// 33
    GCODE_UnhandledCommand,	// 34
    GCODE_UnhandledCommand,	// 35
    GCODE_UnhandledCommand,	// 36
    GCODE_UnhandledCommand,	// 37
    GCODE_UnhandledCommand,	// 38
    GCODE_UnhandledCommand,	// 39
    GCODE_UnhandledCommand,	// 40
    GCODE_UnhandledCommand,	// 41
    GCODE_UnhandledCommand,	// 42
    GCODE_UnhandledCommand,	// 43
    GCODE_UnhandledCommand,	// 44
    GCODE_UnhandledCommand,	// 45
    GCODE_UnhandledCommand,	// 46
    GCODE_UnhandledCommand,	// 47
    GCODE_UnhandledCommand,	// 48
    GCODE_UnhandledCommand,	// 49
    GCODE_UnhandledCommand,	// 50
    GCODE_UnhandledCommand,	// 51
    GCODE_UnhandledCommand,	// 52
    GCODE_UnhandledCommand,	// 53
    GCODE_UnhandledCommand,	// 54
    GCODE_UnhandledCommand,	// 55
    GCODE_UnhandledCommand,	// 56
    GCODE_UnhandledCommand,	// 57
    GCODE_UnhandledCommand,	// 58
    GCODE_UnhandledCommand,	// 59
    GCODE_UnhandledCommand,	// 60
    GCODE_UnhandledCommand,	// 61
    GCODE_UnhandledCommand,	// 62
    GCODE_UnhandledCommand,	// 63
    GCODE_UnhandledCommand,	// 64
    GCODE_UnhandledCommand,	// 65
    GCODE_UnhandledCommand,	// 66
    GCODE_UnhandledCommand,	// 67
    GCODE_UnhandledCommand,	// 68
    GCODE_UnhandledCommand,	// 69
    GCODE_UnhandledCommand,	// 70
    GCODE_UnhandledCommand,	// 71
    GCODE_UnhandledCommand,	// 72
    GCODE_UnhandledCommand,	// 73
    GCODE_UnhandledCommand,	// 74
    GCODE_UnhandledCommand,	// 75
    GCODE_UnhandledCommand,	// 76
    GCODE_UnhandledCommand,	// 77
    GCODE_UnhandledCommand,	// 78
    GCODE_UnhandledCommand,	// 79
    GCODE_UnhandledCommand,	// 80
    GCODE_UnhandledCommand,	// 81
    GCODE_UnhandledCommand,	// 82
    GCODE_UnhandledCommand,	// 83
    GCODE_UnhandledCommand,	// 84
    GCODE_UnhandledCommand,	// 85
    GCODE_UnhandledCommand,	// 86
    GCODE_UnhandledCommand,	// 87
    GCODE_UnhandledCommand,	// 88
    GCODE_UnhandledCommand,	// 89
    GCODE_UnhandledCommand,	// 90
    GCODE_UnhandledCommand,	// 91
    GCODE_UnhandledCommand,	// 92
    GCODE_UnhandledCommand,	// 93
    GCODE_UnhandledCommand,	// 94
    GCODE_UnhandledCommand,	// 95
    GCODE_UnhandledCommand,	// 96
    GCODE_UnhandledCommand,	// 97
    GCODE_UnhandledCommand,	// 98
    GCODE_UnhandledCommand,	// 99
    GCODE_UnhandledCommand,	// 100
    GCODE_UnhandledCommand,	// 101
    GCODE_UnhandledCommand,	// 102
    GCODE_UnhandledCommand,	// 103
    GCODE_UnhandledCommand,	// 104
    GCODE_UnhandledCommand,	// 105
    GCODE_UnhandledCommand,	// 106
    GCODE_UnhandledCommand,	// 107
    GCODE_UnhandledCommand,	// 108
    GCODE_UnhandledCommand,	// 109
    GCODE_UnhandledCommand, // 110
    GCODE_UnhandledCommand, // 111
    GCODE_UnhandledCommand, // 112
    GCODE_UnhandledCommand, // 113
    GCODE_UnhandledCommand, // 114
    GCODE_UnhandledCommand, // 115
    GCODE_UnhandledCommand, // 116
    GCODE_UnhandledCommand, // 117
    GCODE_UnhandledCommand, // 118
    GCODE_UnhandledCommand, // 119
    GCODE_UnhandledCommand, // 120
    GCODE_UnhandledCommand, // 121
    GCODE_UnhandledCommand, // 122
    GCODE_UnhandledCommand, // 123
    GCODE_UnhandledCommand, // 124
    GCODE_UnhandledCommand, // 125
    GCODE_UnhandledCommand, // 126
    GCODE_UnhandledCommand, // 127
    GCODE_UnhandledCommand, // 128
    GCODE_UnhandledCommand, // 129
    GCODE_UnhandledCommand, // 130
    GCODE_UnhandledCommand, // 131
    GCODE_UnhandledCommand, // 132
    GCODE_UnhandledCommand, // 133
    GCODE_UnhandledCommand, // 134
    GCODE_UnhandledCommand, // 135
    GCODE_UnhandledCommand, // 136
    GCODE_UnhandledCommand, // 137
    GCODE_UnhandledCommand, // 138
    GCODE_UnhandledCommand, // 139
    GCODE_UnhandledCommand, // 140
    GCODE_UnhandledCommand, // 141
    GCODE_UnhandledCommand, // 142
    GCODE_UnhandledCommand, // 143
    GCODE_UnhandledCommand, // 144
    GCODE_UnhandledCommand, // 145
    GCODE_UnhandledCommand, // 146
    GCODE_UnhandledCommand, // 147
    GCODE_UnhandledCommand, // 148
    GCODE_UnhandledCommand, // 149
    GCODE_UnhandledCommand, // 150
    GCODE_UnhandledCommand, // 151
    GCODE_UnhandledCommand, // 152
    GCODE_UnhandledCommand, // 153
    GCODE_UnhandledCommand, // 154
    GCODE_UnhandledCommand, // 155
    GCODE_UnhandledCommand, // 156
    GCODE_UnhandledCommand, // 157
    GCODE_UnhandledCommand, // 158
    GCODE_UnhandledCommand, // 159
    GCODE_UnhandledCommand, // 160
    GCODE_UnhandledCommand, // 161
    GCODE_UnhandledCommand, // 162
    GCODE_UnhandledCommand, // 163
    GCODE_UnhandledCommand, // 164
    GCODE_UnhandledCommand, // 165
    GCODE_UnhandledCommand, // 166
    GCODE_UnhandledCommand, // 167
    GCODE_UnhandledCommand, // 168
    GCODE_UnhandledCommand, // 169
    GCODE_UnhandledCommand, // 170
    GCODE_UnhandledCommand, // 171
    GCODE_UnhandledCommand, // 172
    GCODE_UnhandledCommand, // 173
    GCODE_UnhandledCommand, // 174
    GCODE_UnhandledCommand, // 175
    GCODE_UnhandledCommand, // 176
    GCODE_UnhandledCommand, // 177
    GCODE_UnhandledCommand, // 178
    GCODE_UnhandledCommand, // 179
    GCODE_UnhandledCommand, // 180
    GCODE_UnhandledCommand, // 181
    GCODE_UnhandledCommand, // 182
    GCODE_UnhandledCommand, // 183
    GCODE_UnhandledCommand, // 184
    GCODE_UnhandledCommand, // 185
    GCODE_UnhandledCommand, // 186
    GCODE_UnhandledCommand, // 187
    GCODE_UnhandledCommand, // 188
    GCODE_UnhandledCommand, // 189
    GCODE_UnhandledCommand, // 190
    GCODE_UnhandledCommand, // 191
    GCODE_UnhandledCommand, // 192
    GCODE_UnhandledCommand, // 193
    GCODE_UnhandledCommand, // 194
    GCODE_UnhandledCommand, // 195
    GCODE_UnhandledCommand, // 196
    GCODE_UnhandledCommand, // 197
    GCODE_UnhandledCommand, // 198
    GCODE_UnhandledCommand, // 199
    GCODE_UnhandledCommand, // 200
    GCODE_UnhandledCommand, // 201
    GCODE_UnhandledCommand, // 202
    GCODE_UnhandledCommand, // 203
    GCODE_UnhandledCommand, // 204
    GCODE_UnhandledCommand, // 205
    GCODE_UnhandledCommand, // 206
    GCODE_UnhandledCommand, // 207
    GCODE_UnhandledCommand, // 208
    GCODE_UnhandledCommand, // 209
    GCODE_UnhandledCommand, // 210
    GCODE_UnhandledCommand, // 211
    GCODE_UnhandledCommand, // 212
    GCODE_UnhandledCommand, // 213
    GCODE_UnhandledCommand, // 214
    GCODE_UnhandledCommand, // 215
    GCODE_UnhandledCommand, // 216
    GCODE_UnhandledCommand, // 217
    GCODE_UnhandledCommand, // 218
    GCODE_UnhandledCommand, // 219
    GCODE_UnhandledCommand, // 220
    GCODE_UnhandledCommand, // 221
    GCODE_UnhandledCommand, // 222
    GCODE_UnhandledCommand, // 223
    GCODE_UnhandledCommand, // 224
    GCODE_UnhandledCommand, // 225
    GCODE_UnhandledCommand, // 226
    GCODE_UnhandledCommand, // 227
    GCODE_UnhandledCommand, // 228
    GCODE_UnhandledCommand, // 229
    GCODE_UnhandledCommand, // 230
    GCODE_UnhandledCommand, // 231
    GCODE_UnhandledCommand, // 232
    GCODE_UnhandledCommand, // 233
    GCODE_UnhandledCommand, // 234
    GCODE_UnhandledCommand, // 235
    GCODE_UnhandledCommand, // 236
    GCODE_UnhandledCommand, // 237
    GCODE_UnhandledCommand, // 238
    GCODE_UnhandledCommand, // 239
    GCODE_UnhandledCommand, // 240
    GCODE_UnhandledCommand, // 241
    GCODE_UnhandledCommand, // 242
    GCODE_UnhandledCommand, // 243
    GCODE_UnhandledCommand, // 244
    GCODE_UnhandledCommand, // 245
    GCODE_UnhandledCommand, // 246
    GCODE_UnhandledCommand, // 247
    GCODE_UnhandledCommand, // 248
    GCODE_UnhandledCommand, // 249
    GCODE_UnhandledCommand, // 250
    GCODE_UnhandledCommand, // 251
    GCODE_UnhandledCommand, // 252
    GCODE_UnhandledCommand, // 253
    GCODE_UnhandledCommand, // 254
    GCODE_UnhandledCommand, // 255
    GCODE_UnhandledCommand, // 256
    GCODE_UnhandledCommand, // 257
    GCODE_UnhandledCommand, // 258
    GCODE_UnhandledCommand, // 259
    GCODE_UnhandledCommand, // 260
    GCODE_UnhandledCommand, // 261
    GCODE_UnhandledCommand, // 262
    GCODE_UnhandledCommand, // 263
    GCODE_UnhandledCommand, // 264
    GCODE_UnhandledCommand, // 265
    GCODE_UnhandledCommand, // 266
    GCODE_UnhandledCommand, // 267
    GCODE_UnhandledCommand, // 268
    GCODE_UnhandledCommand, // 269
    GCODE_UnhandledCommand, // 270
    GCODE_UnhandledCommand, // 271
    GCODE_UnhandledCommand, // 272
    GCODE_UnhandledCommand, // 273
    GCODE_UnhandledCommand, // 274
    GCODE_UnhandledCommand, // 275
    GCODE_UnhandledCommand, // 276
    GCODE_UnhandledCommand, // 277
    GCODE_UnhandledCommand, // 278
    GCODE_UnhandledCommand, // 279
    GCODE_UnhandledCommand, // 280
    GCODE_UnhandledCommand, // 281
    GCODE_UnhandledCommand, // 282
    GCODE_UnhandledCommand, // 283
    GCODE_UnhandledCommand, // 284
    GCODE_UnhandledCommand, // 285
    GCODE_UnhandledCommand, // 286
    GCODE_UnhandledCommand, // 287
    GCODE_UnhandledCommand, // 288
    GCODE_UnhandledCommand, // 289
    GCODE_UnhandledCommand, // 290
    GCODE_UnhandledCommand, // 291
    GCODE_UnhandledCommand, // 292
    GCODE_UnhandledCommand, // 293
    GCODE_UnhandledCommand, // 294
    GCODE_UnhandledCommand, // 295
    GCODE_UnhandledCommand, // 296
    GCODE_UnhandledCommand, // 297
    GCODE_UnhandledCommand, // 298
    GCODE_UnhandledCommand, // 299
    GCODE_UnhandledCommand, // 300
    GCODE_UnhandledCommand,	// 301: this is the invalid number command
};

/*
 * placeholder for any incomplete commands
 */
bool GCODE_UnhandledCommand(GCODE *command)
{
	uint8_t errStr[] = "This instruction is not yet handled\r\n";
	CDC_Transmit_FS(errStr, sizeof(errStr));

	return (false);
}

/*
 * M17 command
 * Enables all motors
 */
bool GCODE_MotorsEnableCommand(GCODE *command)
{

	motorsEnabled = true;

	return (false);
}

/*
 * M18 command
 * Disable all motors
 */
bool GCODE_MotorsDisableCommand(GCODE *command)
{
	motorsEnabled = false;

	return (false);
}

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
				break;
			default:
				/// \todo missing code
				break;
		}
	} else
	{
		// should never get here
	}
}

