/*
 * FND.h
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_FND_FND_H_
#define DRIVER_FND_FND_H_
#include <stdint.h>
#include "stm32f4xx.h"
#include "GPIO.h"

void FND_WriteData(uint16_t data);
uint16_t FND_ReadData();
void FND_DispData(int state,uint32_t c_msecound,uint32_t s_msecound,uint32_t s_dsecound);
void FND_Init();
void dot_On();
void dot_Off();


#endif /* DRIVER_FND_FND_H_ */
