/*
 * motor.h
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_MOTOR_MOTOR_H_
#define DRIVER_MOTOR_MOTOR_H_

#include "stm32f4xx_hal.h"
#include "tim.h"

void Motor_Init(TIM_HandleTypeDef *htim, uint32_t channel);
void Motor_SetDuty(uint8_t percent);
void Motor_Start();
void Motor_Stop();
extern uint8_t motorPower;

#endif /* DRIVER_MOTOR_MOTOR_H_ */
