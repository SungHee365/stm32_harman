/*
 * Power.c
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */

#include "Power.h"

void Power_UP()
{
	if (motorPower < 100) motorPower += 10;
	Presenter_SetMotorPower(motorPower);
}

void Power_DOWN()
{
	if (motorPower >= 30) motorPower -= 10;
	Presenter_SetMotorPower(motorPower);
}
