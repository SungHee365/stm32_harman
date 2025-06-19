/*
 * Button.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#include "Button.h"


void Button_Init(Button_Handler_t *hbtn, GPIO_TypeDef *GPIOx, uint32_t pinNum)
{
	hbtn -> GPIOx = GPIOx;
	hbtn -> pinNum = pinNum;
	hbtn -> prevState = RELEASED;


	GPIO_Init(hbtn->GPIOx, hbtn -> pinNum, INPUT);
}

button_state_t Button_GetState(Button_Handler_t *hbtn)
{
//	static uint32_t prevState = RELEASED;
	uint32_t curState;
	curState = GPIO_ReadPin(hbtn -> GPIOx, hbtn -> pinNum); // nomal state is high.

	if ((hbtn -> prevState == RELEASED) && (curState == PUSHED) ) // button released -> pushed
	{
		delay(2); //debounce
		hbtn->prevState = PUSHED;
		return ACT_PUSHED;
	}
	else if((hbtn -> prevState == PUSHED) && (curState == RELEASED))
	{
		delay(2); // debounce
		hbtn->prevState = RELEASED;
		return ACT_RELEASED;
	}
	return NO_ACT;
}
