/*
 * logging_config.h
 *
 *  Created on: 16.08.2022
 *      Author: butch
 */

#ifndef LOGGING_CONFIG_H_
#define LOGGING_CONFIG_H_




// define logging options

#define LOGGING_ENABLED 1
#if LOGGING_ENABLED
	/**
	* 0 - LOG_LEVEL_SILENT     no output
	* 1 - LOG_LEVEL_FATAL      fatal errors
	* 2 - LOG_LEVEL_ERROR      all errors
	* 3 - LOG_LEVEL_WARNING    errors, and warnings
	* 4 - LOG_LEVEL_NOTICE     errors, warnings and notices
	* 5 - LOG_LEVEL_TRACE      errors, warnings, notices & traces
	* 6 - LOG_LEVEL_VERBOSE    all
	*/
	#define LOGGING_LOGLEVEL 6

	#define DEBUG_CALCULATE_MOVE_ITERATION_ID 0

	#define DEBUG_SERVO_KEYFRAME_ANIMATOR_GROUP_CALCULATE_SERVO_POSITIONS 0
	#define DEBUG_SERVO_KEYFRAME_ANIMATOR_GET_CALCULATED_SERVO_POSITION 0

	#define DEBUG_ENHANCED_SERVO_SET_TRIM 0
	#define DEBUG_ENHANCED_SERVO_ENHANCED_WRITE 0

	#define DEBUG_SETUP 1
#endif



#endif /* LOGGING_CONFIG_H_ */
