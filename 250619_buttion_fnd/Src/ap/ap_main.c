/*
 * ap_main.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#include "ap_main.h"

enum {RUN, CLEAR, STOP};

Button_Handler_t hBtnRUN;
Button_Handler_t hBtnCLEAR;
Button_Handler_t hBtnSTOP;

int ap_main()
{
	uint32_t data = 0;
	int FND_state = STOP;

	while(1)
	{
		switch (FND_state)
		{
		case RUN:
			if(Button_GetState(&hBtnSTOP) == ACT_PUSHED) FND_state = STOP;
			data += 1;
			//LedBar_Write(data);
			break;
		case CLEAR:
			data = 0;
			FND_state = STOP;
			break;
		case STOP:
			if(Button_GetState(&hBtnRUN) == ACT_PUSHED) FND_state = RUN;
			if(Button_GetState(&hBtnCLEAR) == ACT_PUSHED) FND_state = CLEAR;
			break;
		}
		FND_Write(data);
	}
	return 0;
}

void ap_init()
{
	SystemClock_Init();
	LedBar_Init();
	Button_Init(&hBtnRUN, GPIOB,5);
	Button_Init(&hBtnCLEAR, GPIOB,3);
	Button_Init(&hBtnSTOP, GPIOA,10);
	FND_Init();

}
