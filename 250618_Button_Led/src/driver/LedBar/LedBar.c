/*
 * LedBar.c
 *
 *  Created on: Jun 18, 2025
 *      Author: kccistc
 */

#include "LedBar.h"

typedef struct {
	GPIO_TypeDef *GPIOx;
	uint32_t pinNum;
} LedBar_TypeDef;

LedBar_TypeDef ledBar[8] = {
		{GPIOA, 0},
		{GPIOA, 1},
		{GPIOA, 4},
		{GPIOB, 0},
		{GPIOC, 1},
		{GPIOC, 0},
		{GPIOC, 2},
		{GPIOC, 3},
};

void LedBar_Write(uint8_t data)
{
	for (int i=0; i<8; i++) {
		if ((data & (1<<i)) == 0) {
			GPIO_WritePin(ledBar[i].GPIOx, ledBar[i].pinNum, PIN_RESET);
		}
		else {
			GPIO_WritePin(ledBar[i].GPIOx, ledBar[i].pinNum, PIN_SET);
		}
	}
}
