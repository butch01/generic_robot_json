#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2022-08-20 21:29:42

#include "Arduino.h"
#include <ArduinoJson.h>
#include <Arduino.h>
#include "globalDefines.h"
#include "ServoKeyframeAnimatorGroup.h"
#include "ServoKeyframeAnimator.h"
#include <ArduinoLog.h>
#include <EnhancedServo.h>
#include "moveConstants.h"
#define IS_ROBOT_TYPE_TEST01 1
#define IS_ROBOT_TYPE_ELEEGO_PENGUIN 2
#include "robot_config_test01.h"

void setupSerial() ;
void setupServoGroupPins(EnhancedServo* servoGroup, const unsigned char* pinsServoGroup,  unsigned char servoGroupId, unsigned char arrayLength) ;
void setup() ;
unsigned char getMovementModeFromCurrentJson() ;
void parseJsonDocGenericAndUpdateKeyframeRow(unsigned char *manualKeyframeServoGroupRow, char *servoGroupName, unsigned char manualKeyframeServoGroupRowLength) ;
void processJsonDocument() ;
void parseJsonDoc() ;
void loop() ;

#include "generic_robot_json.ino"


#endif
