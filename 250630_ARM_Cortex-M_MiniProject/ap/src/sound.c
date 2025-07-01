/*
 * sound.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#include "sound.h"

void Sound_Init()
{
	Buzzer_Init(&htim3, TIM_CHANNEL_1);
}

void Sound_Power()
{
    for (int freq = 400; freq <= 1000; freq += 100) {
        Buzzer_SetFreq(freq);
        Buzzer_Start();
        HAL_Delay(30); // 빠르게 주파수 상승
    }
    Buzzer_Stop();

}

void Sound_PowerOff()
{
}

void Sound_ChangeMode()
{

}

void Sound_Alarm()
{

}

