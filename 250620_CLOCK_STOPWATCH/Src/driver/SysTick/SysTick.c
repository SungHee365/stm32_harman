/*
 * SysTick.c
 *
 *  Created on: Jun 20, 2025
 *      Author: kccistc
 */

#include "SysTick.h"

static uint32_t tick=0;


void incTick()
{
	tick++;
}

uint32_t getTick()
{
	return tick;
}
