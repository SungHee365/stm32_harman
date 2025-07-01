/*
 * motor.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */


#include "motor.h"

static TIM_HandleTypeDef *hmotorTim;
static uint32_t motorTimChannel;
uint8_t motorPower = 50;

void Motor_Init(TIM_HandleTypeDef *htim, uint32_t channel)
{
	hmotorTim = htim;
	motorTimChannel = channel;
}

void Motor_SetDuty(uint8_t percent) // 0~100 (%)
{
    if (percent > 100) percent = 100;

    uint32_t arr = __HAL_TIM_GET_AUTORELOAD(hmotorTim);
    uint32_t ccr = (arr + 1) * percent / 100;

    __HAL_TIM_SET_COMPARE(hmotorTim, motorTimChannel, ccr);
}

void Motor_Start()
{
	HAL_TIM_PWM_Start(hmotorTim, motorTimChannel);
}

void Motor_Stop()
{
	HAL_TIM_PWM_Stop(hmotorTim, motorTimChannel);
}
