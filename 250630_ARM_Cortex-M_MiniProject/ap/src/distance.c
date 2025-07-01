/*
 * distance.c
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */
#include "distance.h"
#include "UltraSonic.h"
static watch_t distance = {DISTANCE, 0,0,0,0,0,0,0};


void Distance_Excute()
{
	static uint32_t prevTick = 0;
	uint32_t curTick = HAL_GetTick();

	if (curTick - prevTick < 1000) return;  // 100ms 주기 제한

	prevTick = curTick;

	distance.dist = UltraSonic_GetDistance();  // 측정
	Presenter_OutData(distance);               // 출력
}
