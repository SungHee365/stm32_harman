/*
 * UltraSonic.h
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_ULTRASONIC_ULTRASONIC_H_
#define DRIVER_ULTRASONIC_ULTRASONIC_H_

#include "stm32f4xx_hal.h"
#include "tim.h"

extern volatile uint32_t rising_time;
extern volatile uint32_t falling_time;
extern volatile uint8_t  is_rising_edge;
extern volatile uint8_t  capture_done;

void UltraSonic_Trigger(void);
int UltraSonic_GetDistance(void);
void UltraSonic_Init(void);

#endif /* DRIVER_ULTRASONIC_ULTRASONIC_H_ */
