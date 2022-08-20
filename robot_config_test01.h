/*
 * config_test01.h
 *
 *  Created on: 15.08.2022
 *      Author: butch
 *
 *      this file contains configuration which is specific for robot of type test01
 */

#ifndef ROBOT_CONFIG_TEST01_H_
#define ROBOT_CONFIG_TEST01_H_

#include <EnhancedServo.h>

/*
 * configure serial communication
 */
#define IS_SERIAL_JSON_ENABLED 1
#if IS_SERIAL_JSON_ENABLED
	// Communication setup for receiving json commands
	#define JSON_SERIAL_NAME Serial
	#define JSON_SERIAL_BAUD 57600
#endif


#define IS_SERIAL_DEBUG_ENABLED 1
#if IS_SERIAL_DEBUG_ENABLED
	// DEBUG SERIAL PORT
	#define DEBUG_SERIAL_NAME Serial2
	#define DEBUG_SERIAL_BAUD 57600
#endif



// defines size keyframe array for MOVE_MANUAL_JSON_KEYFRAMESET -> at first keep same size for all servo groups
#define MOVE_MANUAL_KEYFRAMESET_MAX_KEYFRAME_COUNT 3

/**
 *		SERVO AND SERVO_GROUP CONFIGURATION START
 *
 *		ServoGroups and the containing servors are defined here
 *
 *		- group 0 for legs
 *		- group 1 for arms
 *
 *		4 servo groups (0 - 3) are supported by the code.
 */

#define NUMBER_OF_SERVOGROUPS 2


#if NUMBER_OF_SERVOGROUPS > 0
	// servo groups for legs
	#define NUMBER_OF_SERVOGROUP_0_SERVOS 6
	EnhancedServo servoGroup0[NUMBER_OF_SERVOGROUP_0_SERVOS];

	// stores the arduino pins in an array. Will be mapped to EnhancedServo[] Array of the servoGroup0
	const static unsigned char  pinsServoGroup0[] PROGMEM = {
		// SERVO_SHOULDER_LEFT_PIN
		30,
		// SERVO_SHOULDER_RIGHT_PIN
		31,
		// SERVO_ARM_UP_LEFT_PIN
		32,
		// SERVO_ARM_UP_RIGHT_PIN
		33,
		// SERVO_ARM_LOW_LEFT_PIN,
		34,
		// SERVO_ARM_LOW_RIGHT_PIN
		35

	};

	// TODO: array for min, max, trim

	// array for manual keyframe set moves. Will also be used for live json movement wich sends values for all servos
	unsigned char manualKeyframeSetServoGroup0[MOVE_MANUAL_KEYFRAMESET_MAX_KEYFRAME_COUNT][NUMBER_OF_SERVOGROUP_0_SERVOS];


#endif


#if NUMBER_OF_SERVOGROUPS > 1
	// servo group for arms
	#define NUMBER_OF_SERVOGROUP_1_SERVOS 6
	EnhancedServo servoGroup1[NUMBER_OF_SERVOGROUP_1_SERVOS];

	const static unsigned char  pinsServoGroup1[] PROGMEM = {
		// SERVO_LEG_UP_LEFT_PIN
		40,
		// SERVO_LEG_UP_RIGHT_PIN
		41,
		// SERVO_LEG_KNEE_LEFT_PIN
		42,
		// SERVO_LEG_KNEE_RIGHT_PIN
		43,
		// SERVO_LEG_ANKLE_LEFT_PIN
		44,
		// SERVO_LEG_ANKLE_RIGHT_PIN
		45
	};

	// array for manual keyframe set moves. Will also be used for live json movement wich sends values for all servos
	// NUMBER_OF_SERVOGROUP_1_SERVOS +1 because the time is also stored for each keyframe
	unsigned char manualKeyframeSetServoGroup1[MOVE_MANUAL_KEYFRAMESET_MAX_KEYFRAME_COUNT][NUMBER_OF_SERVOGROUP_1_SERVOS +1];


#endif

#if NUMBER_OF_SERVOGROUPS > 2
	// servo group for arms
	#define NUMBER_OF_SERVOGROUP_2_SERVOS 2
	EnhancedServo servoGroup2[NUMBER_OF_SERVOGROUP_2_SERVOS];
	const static  unsigned char  pinsServoGroup2[] PROGMEM = {
		0,1
	};
	// array for manual keyframe set moves. Will also be used for live json movement wich sends values for all servos
	unsigned char manualKeyframeSetServoGroup2[MOVE_MANUAL_KEYFRAMESET_MAX_KEYFRAME_COUNT][NUMBER_OF_SERVOGROUP_2_SERVOS];

#endif

#if NUMBER_OF_SERVOGROUPS > 3
	// servo group for arms
	#define NUMBER_OF_SERVOGROUP_3_SERVOS 2
	EnhancedServo servoGroup3[NUMBER_OF_SERVOGROUP_3_SERVOS];
	const static unsigned char  pinsServoGroup3[] PROGMEM = {
		2,3
	};

	// array for manual keyframe set moves. Will also be used for live json movement wich sends values for all servos
	unsigned char manualKeyframeSetServoGroup3[MOVE_MANUAL_KEYFRAMESET_MAX_KEYFRAME_COUNT][NUMBER_OF_SERVOGROUP_3_SERVOS];

#endif


/**
*		SERVO AND SERVO_GROUP CONFIGURATION END
*/


#endif /* ROBOT_CONFIG_TEST01_H_ */
