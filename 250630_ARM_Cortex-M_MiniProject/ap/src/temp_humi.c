/*
 * distance.c
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */
#include "temp_humi.h"
#include "dht11.h"
static watch_t temp_humi = {TEMP_HUMI, 0,0,0,0,0,0,0};


void Temp_Humi_Excute()
{
	static uint32_t prevTick = 0;
	uint32_t curTick = HAL_GetTick();

	if (curTick - prevTick < 5000) return;  // 100ms 주기 제한

	prevTick = curTick;
	uint8_t temp = 0, humi = 0;
	if (DHT11_Read(&temp, &humi)) {
		// 온도: 상위 바이트, 습도: 하위 바이트로 저장
		temp_humi.id = TEMP_HUMI;
		temp_humi.temp = temp;
		temp_humi.humi = humi;
	}
		Presenter_OutData(temp_humi);               // 출력
}
