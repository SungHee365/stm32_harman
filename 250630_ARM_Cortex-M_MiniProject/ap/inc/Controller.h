/*
 * Controller.h
 *
 *  Created on: Jun 24, 2025
 *      Author: rhoblack
 */

#ifndef AP_CONTROLLER_H_
#define AP_CONTROLLER_H_

#include "stopWatch.h"
#include "timeWatch.h"
#include "distance.h"
#include "temp_humi.h"
#include "Model_Watch.h"
#include "rotate.h"
#include "Power.h"


enum {NO_CONTROL, MODE, UP_POWER, DOWN_POWER, DISTANCE_MEASURED, TEMPHUMI};
enum {MODE_NO_ACT, MODE_ACT, UP_ACT, DOWN_ACT, DISTANCE_ACK, TEMP_HUMI_ACK};

typedef struct {
	int id;
	int data;
}inputData_TypeDef;

void Controller_SetInputData(inputData_TypeDef inputData);
void Controller_Excute();

#endif /* AP_CONTROLLER_H_ */
