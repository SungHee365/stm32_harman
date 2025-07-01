/*
 * rotate.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */


#include "rotate.h"

void Rotate_Init()
{
	Motor_Init(&htim1, TIM_CHANNEL_1);
}

void Rotate_On()
{
	Motor_SetDuty(motorPower);
//	Motor_Start();
}
