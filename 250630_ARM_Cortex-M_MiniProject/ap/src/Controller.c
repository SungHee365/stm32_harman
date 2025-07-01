/*
 * Controller.c
 *
 *  Created on: Jun 24, 2025
 *      Author: rhoblack
 */
#include "Controller.h"


typedef enum {/*S_TIME_WATCH, S_STOP_WATCH,*/ S_DISTANCE, S_TEMP_HUMI} watchModeState_t;

void Controller_Mode();


inputData_TypeDef controlData = {0};
static watchModeState_t modeState = S_DISTANCE;

void Controller_Excute()
{
	Controller_Mode();
}

void Controller_SetInputData(inputData_TypeDef inputData)
{
	if (inputData.id == MODE) {
		controlData.id = MODE;
		controlData.data = MODE_ACT;
	}

	else if (inputData.id == UP_POWER) {
		Power_UP();
		LED_Level_Check();
	}
	else if (inputData.id == DOWN_POWER) {
		Power_DOWN();
		LED_Level_Check();
	}

	else if (inputData.id == DISTANCE_MEASURED){
		controlData.id = DISTANCE_MEASURED;
		controlData.data = inputData.data;
	}
	else if (inputData.id == TEMP_HUMI){
		controlData.id = TEMP_HUMI;
		controlData.data = inputData.data;
	}
}

void Controller_Mode()
{
	switch(modeState)
	{
/*
	case S_TIME_WATCH:
		if (controlData.id == MODE) {
			controlData.id = NO_CONTROL;
			modeState = S_STOP_WATCH;
		}
		TimeWatch_Excute();
		break;
	case S_STOP_WATCH:
		if (controlData.id == MODE) {
			controlData.id = NO_CONTROL;
			modeState = S_DISTANCE;
		}
		StopWatch_Excute();
		break;
*/
    case S_DISTANCE:
        if (controlData.id == MODE) {
            controlData.id = NO_CONTROL;
            modeState = S_TEMP_HUMI;

        }
        Distance_Excute();
        break;
    case S_TEMP_HUMI:
        if (controlData.id == MODE) {
            controlData.id = NO_CONTROL;
            modeState = S_DISTANCE;
        }
        Temp_Humi_Excute();
        break;
	}
}

