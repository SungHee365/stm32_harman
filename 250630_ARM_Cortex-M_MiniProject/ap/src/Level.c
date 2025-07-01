/*
 * Level.c
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */
#include "Level.h"
#include "Presenter.h"

uint8_t level;
uint8_t ledData;

void LED_Level_Check()
{
	// motorPower (0~100)를 8단계 (0~8)로 변환
	level = motorPower / 10 - 2;  // 100/8 ≈ 12.5 → 13으로 나눔
	ledData = (1 << level) - 1; // 예: level=3이면 0b00000111
	Presenter_Led_Check(ledData);
}

void LED_Level_Init()
{
	level = motorPower / 10 - 2;  // 100/8 ≈ 12.5 → 13으로 나눔
	ledData = (1 << level) - 1; // 예: level=3이면 0b00000111
	Presenter_Led_Check(ledData);
}
