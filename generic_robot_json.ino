#include <ArduinoJson.h>
#include <Arduino.h>
#include "globalDefines.h"
#include "ServoKeyframeAnimatorGroup.h"
#include "ServoKeyframeAnimator.h"
#include <ArduinoLog.h>
#include <EnhancedServo.h>
#include "moveConstants.h"


// SELECT ROBOT CONFIGURATION

// define robot type here. Each robot type will have it's own include file
// only one Robot
#define IS_ROBOT_TYPE_TEST01 1
#define IS_ROBOT_TYPE_ELEEGO_PENGUIN 2


#if IS_ROBOT_TYPE_TEST01
	// IS_ROBOT_TYPE_TEST01 is choosen
	#include "robot_config_test01.h"
#elif IS_ROBOT_TYPE_ELEEGO_PENGUIN
	// IS_ROBOT_TYPE_ELEEGO_PENGUIN is choosen
	#include "robot_config_eleego_penguin.h"
#endif


unsigned char movementMode = 0;


// static json document for communication
StaticJsonDocument<200> doc;


/**
 * setup the serial ports
 * 	- for json communication
 * 	- for DEBUG Serial
 *
 * 	The configuration is outsourced to robot_config_*.h
 */
void setupSerial()
{
	#if IS_SERIAL_JSON_ENABLED
	// initialize serials
		JSON_SERIAL_NAME.begin(JSON_SERIAL_BAUD);
		 while (!JSON_SERIAL_NAME) continue;
	#endif

	#if IS_SERIAL_DEBUG_ENABLED
		DEBUG_SERIAL_NAME.begin(DEBUG_SERIAL_BAUD);
		while (!DEBUG_SERIAL_NAME) continue;
	#endif

	#if LOGGING_ENABLED
	    Log.begin   (LOGGING_LOGLEVEL, &DEBUG_SERIAL_NAME);
	#endif
}


/**
 * initializes a referenced keyframe set with the center value of the servo
 * keyframe has following format: time, servo0, servo1, ..., servoN
 */
void setupServoGroupKeyframeSet(EnhancedServo* servoGroup,  unsigned char servoGroupId, unsigned char keyframeId, unsigned char* manualKeyframeSet, unsigned char keyframeLength, unsigned char defaultTime=100)
{



	// set default time for keyframe
	manualKeyframeSet[0] = defaultTime;
	#if DEBUG_SETUP
		Log.verboseln(F("%s: setting up (servoGroup%d keyframe[%d][%d] = %d (time)"), __FUNCTION__, servoGroupId, keyframeId, 0, defaultTime);
	#endif

	// iterate over servos (run from 1 instead of 0, because 0 is the time. servos are starting at 1)
	for (unsigned char servo = 1; servo < keyframeLength; servo++)
	{
		unsigned char centerValue = servoGroup[servo -1].getTrim() + SERVO_DEFAULT_CENTER;
		manualKeyframeSet[servo] = centerValue;
		#if DEBUG_SETUP
			Log.verboseln(F("%s: setting up (servoGroup%d keyframe[%d][%d] = %d"), __FUNCTION__, servoGroupId, keyframeId, servo, centerValue );
		#endif

	}
}


/**
 * setup the servo group pins
 *
 * 	The configuration is outsourced to robot_config_*.h (depending on the active configuration)
 */
void setupServoGroupPins(EnhancedServo* servoGroup, const unsigned char* pinsServoGroup,  unsigned char servoGroupId, unsigned char arrayLength)
{
	// value of NUMBER_OF_SERVOGROUP_X_SERVOS
	unsigned char countOfServos=0;


	// setup the pins
	for (unsigned char i; i< arrayLength; i++)
	{
		// attach the servo to the pin, configured in pinsServoGroup0 array
		unsigned char pin = pgm_read_word(&pinsServoGroup[i]);
		servoGroup[i].attach(pin);
		#if DEBUG_SETUP
			Log.verboseln(F("%s: Attaching servoGroup%d[%d] to pin [%d]"), __FUNCTION__,  servoGroupId, i, pin);
		#endif
	}

}

//The setup function is called once at startup of the sketch
void setup()
{
	// setup the serial ports
	setupSerial();
	#if LOGGING_ENABLED
		Log.traceln(F("%s: starting..."), __FUNCTION__);
	#endif


	// setup the servo groups
	#if NUMBER_OF_SERVOGROUPS > 0
		setupServoGroupPins(servoGroup0, pinsServoGroup0, 0, sizeof (servoGroup0) / sizeof servoGroup0[0]);

		// cannot give pointer to 2d array as argument. So I need to iterate through the number of keyframe and set each keyframe
		for (unsigned char k; k < MOVE_MANUAL_KEYFRAMESET_MAX_KEYFRAME_COUNT; k++ )
		{
			setupServoGroupKeyframeSet(servoGroup0, 0, k, manualKeyframeSetServoGroup0[k], NUMBER_OF_SERVOGROUP_0_SERVOS+1, KEYFRAME_DEFAULT_TIME);
		}
	#endif
	#if NUMBER_OF_SERVOGROUPS > 1
		setupServoGroupPins(servoGroup1, pinsServoGroup1, 1, sizeof (servoGroup1) / sizeof servoGroup1[0]);

		// cannot give pointer to 2d array as argument. So I need to iterate through the number of keyframe and set each keyframe
		for (unsigned char k; k < MOVE_MANUAL_KEYFRAMESET_MAX_KEYFRAME_COUNT; k++ )
		{
			setupServoGroupKeyframeSet(servoGroup1, 1, k, manualKeyframeSetServoGroup1[k], NUMBER_OF_SERVOGROUP_1_SERVOS+1, KEYFRAME_DEFAULT_TIME);
		}
	#endif
	#if NUMBER_OF_SERVOGROUPS > 2
		setupServoGroupPins(servoGroup2, pinsServoGroup2, 2, sizeof (servoGroup2) / sizeof servoGroup2[0]);
		// cannot give pointer to 2d array as argument. So I need to iterate through the number of keyframe and set each keyframe
		for (unsigned char k; k < MOVE_MANUAL_KEYFRAMESET_MAX_KEYFRAME_COUNT; k++ )
		{
			setupServoGroupKeyframeSet(servoGroup2, 2, k, manualKeyframeSetServoGroup2[k], NUMBER_OF_SERVOGROUP_2_SERVOS+1, KEYFRAME_DEFAULT_TIME);
		}
	#endif
	#if NUMBER_OF_SERVOGROUPS > 3
		setupServoGroupPins(servoGroup3, pinsServoGroup3, 3, sizeof (servoGroup3) / sizeof servoGroup3[0]);
		// cannot give pointer to 2d array as argument. So I need to iterate through the number of keyframe and set each keyframe
		for (unsigned char k; k < MOVE_MANUAL_KEYFRAMESET_MAX_KEYFRAME_COUNT; k++ )
		{
			setupServoGroupKeyframeSet(servoGroup3, 3, k, manualKeyframeSetServoGroup3[k], NUMBER_OF_SERVOGROUP_3_SERVOS+1, KEYFRAME_DEFAULT_TIME);
		}
	#endif

//		uintptr_t address = &manualKeyframeSetServoGroup0[0][0];
//		DEBUG_SERIAL_NAME.println("aaaaaaaaaaa");
//		DEBUG_SERIAL_NAME.print("address=");
//		DEBUG_SERIAL_NAME.println(address);
//		DEBUG_SERIAL_NAME.print("manualKeyframeSetServoGroup0[0][0]=");
//		DEBUG_SERIAL_NAME.println(manualKeyframeSetServoGroup0[0][0]);
//		unsigned char *value = *reinterpret_cast<unsigned char  *>(address);
//		DEBUG_SERIAL_NAME.print("value=");
//		DEBUG_SERIAL_NAME.println(value[0][0]);
////		DEBUG_SERIAL_NAME.print("value[1]=");
////		DEBUG_SERIAL_NAME.println(value[1]);
////		DEBUG_SERIAL_NAME.println("xxxxx");




}


/**
 * parses the movementMode from the current json document
 * return: movementMode
 */
unsigned char getMovementModeFromCurrentJson()
{
	unsigned char movementMode=doc["m"];
	#if DEBUG_JSON_PARSING
		Log.traceln(F("%s: movementMode=%d"),__FUNCTION__, movementMode);
	#endif

	return  movementMode;
}


/**
 * parse the json and update the given keyframe row (single row only)
 * parses:
 * - time
 * - servo positions
 */
void parseJsonDocGenericAndUpdateKeyframeRow(unsigned char *manualKeyframeServoGroupRow, char *servoGroupName, unsigned char manualKeyframeServoGroupRowLength)
{

	unsigned char value=0;

	unsigned char time=doc["t"];
	for (unsigned char servo=1; servo <= manualKeyframeServoGroupRowLength;  servo++)
		{

			String id=String(servo-1);
			value=doc[servoGroupName][id];
			manualKeyframeSetServoGroup0[0][servo] = value;
			#if DEBUG_JSON_PARSING
				Log.traceln("%s: servo=%d, value from doc=%d", __FUNCTION__, servo, value);
			#endif

		}
}

/**
 * processes the json document
 */
void processJsonDocument()
{
	unsigned char movementMode = getMovementModeFromCurrentJson();
	switch (movementMode)
	{
		case MOVE_MANUAL_JSON_LIVE:
			// iterate over the servoGroups:
			for (int i=0; i<NUMBER_OF_SERVOGROUPS; i++)
			{
				// build the servorgroup name (static text + dynamic id)
				String sg = "sg" + String(i);

				// check if the desired servogroup is inside the json document
				if (doc.containsKey(sg))
				{
					// iterate over the ids of the supported amount of servo groups

					switch (i)
					{
						case 0:
							#if DEBUG_PROCESS_JSON_DOCUMENT
								Log.traceln(F("%s: movementMode=%d calling parseJsonDocGenericAndUpdateKeyframeRow for sg%d, length %d "), __FUNCTION__, movementMode, i, sizeof (manualKeyframeSetServoGroup0[0]));
							#endif
							parseJsonDocGenericAndUpdateKeyframeRow(manualKeyframeSetServoGroup0[0], "sg0", sizeof (manualKeyframeSetServoGroup0[0]));
							break;

						#if NUMBER_OF_SERVOGROUPS > 1
							case 1:
								#if DEBUG_PROCESS_JSON_DOCUMENT
									Log.traceln(F("%s: movementMode=%d calling parseJsonDocGenericAndUpdateKeyframeRow for sg%d, length %d "), __FUNCTION__, movementMode, i, sizeof (manualKeyframeSetServoGroup1[0]));
								#endif
								parseJsonDocGenericAndUpdateKeyframeRow(manualKeyframeSetServoGroup1[0], "sg1", sizeof (manualKeyframeSetServoGroup0[1]));
								break;
						#endif
						#if NUMBER_OF_SERVOGROUPS > 2
							case 2:
								#if DEBUG_PROCESS_JSON_DOCUMENT
									Log.traceln(F("%s: movementMode=%d calling parseJsonDocGenericAndUpdateKeyframeRow for sg%d, length %d "), __FUNCTION__, movementMode, i, sizeof (manualKeyframeSetServoGroup2[0]));
								#endif
								parseJsonDocGenericAndUpdateKeyframeRow(manualKeyframeSetServoGroup2[0], "sg2", sizeof (manualKeyframeSetServoGroup2[0])));
								break;
						#endif
						#if NUMBER_OF_SERVOGROUPS > 3
							case 3:
								#if DEBUG_PROCESS_JSON_DOCUMENT
									Log.traceln(F("%s: movementMode=%d calling parseJsonDocGenericAndUpdateKeyframeRow for sg%d, length %d "), __FUNCTION__, movementMode, i, sizeof (manualKeyframeSetServoGroup3[0]);
								#endif
								parseJsonDocGenericAndUpdateKeyframeRow(manualKeyframeSetServoGroup3[0], "sg3", sizeof (manualKeyframeSetServoGroup3[0])));
								break;
						#endif
					}
				}
				else
				{
					Log.trace("missing sg%d", i);
				}
			}
			break;
	}

}

void parseJsonDoc()
{
	unsigned char  time=doc["t"];
	movementMode = doc["m"];

	#if DEBUG_JSON_PARSING
		Log.traceln(F("%s: time=%d, mm=%d"), __FUNCTION__, time, movementMode);
	#endif
	if (movementMode == MOVE_MANUAL_JSON_LIVE )
	{
	#if NUMBER_OF_SERVOGROUPS > 1
		String sg="sg0";
		unsigned char value=0;

		manualKeyframeSetServoGroup0[0][0]=time;
		for (unsigned char servo=1; servo <= sizeof (manualKeyframeSetServoGroup0[0]);  servo++)
		{

			String id=String(servo-1);
			value=doc[sg][id];
			manualKeyframeSetServoGroup0[0][servo] = value;
			#if DEBUG_JSON_PARSING
				Log.traceln("servo=%d, value from doc=%d", servo,value);
			#endif

		}
	#endif
	}

}

// The loop function is called in an endless loop
void loop()
{

	// parse new json commands if available
	if (JSON_SERIAL_NAME.available() > 0)
	{
		// parse the json from JSON_SERIAL_NAME, catch error information if parsing fails
		DeserializationError jsonParsingError = deserializeJson(doc, JSON_SERIAL_NAME);
		if (jsonParsingError) {
			DEBUG_SERIAL_NAME.print(F("deserializeJson() failed: "));
			DEBUG_SERIAL_NAME.println(jsonParsingError.f_str());
		return;
		}
//		parseJsonDoc();
		processJsonDocument();


	}


}
