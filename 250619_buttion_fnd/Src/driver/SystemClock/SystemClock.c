/*
 * SystemClock.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */
#include "SystemClock.h"

void SystemClock_Init()
{
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
}

void delay(int loop)
{
	for(int j=0; j<loop; j++ ){
		for(int i=0; i<1000; i++);
	}
}
