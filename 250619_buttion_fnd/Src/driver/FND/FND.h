/*
 * FND.h
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_FND_FND_H_
#define DRIVER_FND_FND_H_
#include <stdint.h>
#include "GPIO.h"
#include "SystemClock.h"

void FND_Init();
void FND_Write(uint32_t data);
void data_digit(uint32_t data);
void data_digit1(uint32_t data);
void data_digit10(uint32_t data);
void data_digit100(uint32_t data);
void data_digit1000(uint32_t data);
void data_bcd(uint32_t data);

#endif /* DRIVER_FND_FND_H_ */
