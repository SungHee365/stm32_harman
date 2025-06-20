/*
 * ap_main.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#include "ap_main.h"

enum {CLOCK, STOPWATCH_STOP, STOPWATCH_RUN, STOPWATCH_CLEAR};
int state = CLOCK;
Button_Handler_t hBtnRUNSTOP;
Button_Handler_t hBtnCLEAR;
Button_Handler_t hBtnOnOff;

typedef struct{
	uint8_t hour;
	uint8_t minute;
	uint8_t secound;
	uint8_t dsecound;
	uint32_t msecound;
	uint16_t counter;
} time_TypeDef;

static time_TypeDef Clock = {12, 0, 0, 0, 0, 0};
static time_TypeDef Stopwatch = {0,0,0,0,0,0};


void TIM2_IRQHandler(void) // 1ms 간격으로 인터럽트 걸림
{

	if(Clock.msecound >= 1000-1) {
		Clock.msecound = 0;
		Clock.secound++;
		if(Clock.secound >= 60-1) {
			Clock.secound = 0;
			Clock.minute++;
			if(Clock.minute >= 60-1){
				Clock.minute = 0;
				Clock.hour++;
				if(Clock.hour >= 24-1) {
					Clock.hour = 0;
				}
			}
		}
	}
	Clock.msecound++;
	Clock.counter = Clock.hour * 100 + Clock.minute;
	if(state==CLOCK) {
		FND_WriteData(Clock.counter);
	}
	FND_DispData(state,Clock.msecound,Stopwatch.msecound,Stopwatch.dsecound);
	incTick();
	TIM_ClearUIF(TIM2);

}

int ap_main()
{
	//	uint8_t data = 1;
	//	uint16_t counter = 0;
	uint32_t prevCounterTime = 0;
	//	int led_state = OFF;


	while(1)
	{


		switch (state)
		{
		case CLOCK:
			if(Button_GetState(&hBtnOnOff) == ACT_PUSHED) state = STOPWATCH_STOP;
			break;
		case STOPWATCH_STOP:
			if(Button_GetState(&hBtnOnOff) == ACT_PUSHED) state = CLOCK;
			else if(Button_GetState(&hBtnRUNSTOP) == ACT_PUSHED) state = STOPWATCH_RUN;
			else if(Button_GetState(&hBtnCLEAR) == ACT_PUSHED) state = STOPWATCH_CLEAR;
			break;
		case STOPWATCH_RUN:
			if(Button_GetState(&hBtnOnOff) == ACT_PUSHED) state = CLOCK;
			else if(Button_GetState(&hBtnRUNSTOP) == ACT_PUSHED) state = STOPWATCH_STOP;
			if (getTick() - prevCounterTime >= 10) {
				prevCounterTime = getTick();
				Stopwatch.msecound++;
				if(Stopwatch.msecound >= 10-1) {
					Stopwatch.msecound = 0;
					Stopwatch.dsecound ++;
					if(Stopwatch.dsecound >= 10-1) {
						Stopwatch.dsecound = 0;
						Stopwatch.secound++;
						if(Stopwatch.secound >= 60-1) {
							Stopwatch.secound = 0;
							Stopwatch.minute++;
							if(Stopwatch.minute >= 10 -1){
								Stopwatch.minute = 0;
							}
						}
					}
				}
			}
			break;
		case STOPWATCH_CLEAR:
			state = STOPWATCH_STOP;
			Stopwatch.dsecound = 0;
			Stopwatch.secound = 0;
			Stopwatch.minute = 0;
			Stopwatch.counter = 0;
			break;
		}



		Stopwatch.counter = 1000*Stopwatch.minute + 10*Stopwatch.secound + Stopwatch.dsecound;
		FND_WriteData(Stopwatch.counter);
	}
	return 0;
}

void ap_init()
{
	SystemClock_Init();
	LedBar_Init();
	Button_Init(&hBtnRUNSTOP, GPIOB,5);
	Button_Init(&hBtnCLEAR, GPIOB,3);
	Button_Init(&hBtnOnOff, GPIOA,10);
	FND_Init();
	TIM_Init(TIM2, 16-1, 1000-1);
	TIM_CntStart(TIM2);
	TIM_UIEnable(TIM2);
	NVIC_EnableIRQ(TIM2_IRQn); // nvic에서 TIM2를 사용하겠다는 뜻

	TIM_Init(TIM5, 16000-1, 0xffffffff);


}
