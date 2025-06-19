/*
 * FND.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#include "FND.h"

typedef struct {
	GPIO_TypeDef *GPIOx;
	uint32_t pinNum;
} FND_TypeDef;

FND_TypeDef fnd_bcd[8] = {
		{GPIOA, 11},
		{GPIOB, 12},
		{GPIOB, 2},
		{GPIOB, 1},
		{GPIOB, 15},
		{GPIOB, 14},
		{GPIOB, 13},
		{GPIOC, 4}
};

FND_TypeDef fnd_d[4] = {
		{GPIOC, 8},
		{GPIOC, 6},
		{GPIOC, 5},
		{GPIOA, 12}
};

void FND_Init()
{
	GPIO_Init(GPIOC, 8, OUTPUT);
	GPIO_Init(GPIOC, 6, OUTPUT);
	GPIO_Init(GPIOC, 5, OUTPUT);
	GPIO_Init(GPIOA, 12, OUTPUT);
	GPIO_Init(GPIOA, 11, OUTPUT);
	GPIO_Init(GPIOB, 12, OUTPUT);
	GPIO_Init(GPIOB, 2, OUTPUT);
	GPIO_Init(GPIOB, 1, OUTPUT);
	GPIO_Init(GPIOB, 15, OUTPUT);
	GPIO_Init(GPIOB, 14, OUTPUT);
	GPIO_Init(GPIOB, 13, OUTPUT);
	GPIO_Init(GPIOC, 4, OUTPUT);
}

void FND_Write(uint32_t data)
{
	/*
	data_digit1(data);
	delay(4);
	data_digit10(data);
	delay(4);
	data_digit100(data);
	delay(4);
	data_digit1000(data);
	delay(4);
	*/
	data_digit(data);
}

void data_digit(uint32_t data)
{
	for (int i=0; i<4; i++) {
		if (i == 3) {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_RESET);
			GPIO_WritePin(fnd_d[0].GPIOx, fnd_d[0].pinNum, PIN_SET);
			GPIO_WritePin(fnd_d[1].GPIOx, fnd_d[1].pinNum, PIN_SET);
			GPIO_WritePin(fnd_d[2].GPIOx, fnd_d[2].pinNum, PIN_SET);
			data_bcd((data/100)%10);
			delay(4);
		}
		else if( i == 2) {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_RESET);
			GPIO_WritePin(fnd_d[0].GPIOx, fnd_d[0].pinNum, PIN_SET);
			GPIO_WritePin(fnd_d[1].GPIOx, fnd_d[1].pinNum, PIN_SET);
			GPIO_WritePin(fnd_d[3].GPIOx, fnd_d[3].pinNum, PIN_SET);
			data_bcd((data/1000)%10);
			delay(4);
		}
		else if( i == 1) {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_RESET);
			GPIO_WritePin(fnd_d[0].GPIOx, fnd_d[0].pinNum, PIN_SET);
			GPIO_WritePin(fnd_d[3].GPIOx, fnd_d[3].pinNum, PIN_SET);
			GPIO_WritePin(fnd_d[2].GPIOx, fnd_d[2].pinNum, PIN_SET);
			data_bcd((data/10000)%10);
			delay(4);
		}
		else if( i == 0) {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_RESET);
			GPIO_WritePin(fnd_d[1].GPIOx, fnd_d[1].pinNum, PIN_SET);
			GPIO_WritePin(fnd_d[3].GPIOx, fnd_d[3].pinNum, PIN_SET);
			GPIO_WritePin(fnd_d[2].GPIOx, fnd_d[2].pinNum, PIN_SET);
			data_bcd((data/100000)%10);
			delay(4);
		}
	}

}

/*
void data_digit1(uint32_t data)
{
	for (int i=0; i<4; i++) {
		if (i == 3) {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_RESET);
		}
		else {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_SET);
		}
	}
	data_bcd((data%1000)/100);
}

void data_digit10(uint32_t data)
{
	for (int i=0; i<4; i++) {
		if (i == 2) {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_RESET);
		}
		else {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_SET);
		}
	}
	data_bcd((data%10000)/1000);
}

void data_digit100(uint32_t data)
{
	for (int i=0; i<4; i++) {
		if (i == 1) {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_RESET);
		}
		else {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_SET);
		}
	}
	data_bcd((data%100000)/10000);
}

void data_digit1000(uint32_t data)
{
	for (int i=0; i<4; i++) {
		if (i == 0) {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_RESET);
		}
		else {
			GPIO_WritePin(fnd_d[i].GPIOx, fnd_d[i].pinNum, PIN_SET);
		}
	}
	data_bcd(data/100000);
}
*/
void data_bcd(uint32_t data)
{
	switch(data)
	{
	case 0:
		for (int i=0; i<8; i++) {
			if ((i == 7) | (i == 6) ) {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_RESET);
			}
			else {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_SET);
			}
		}
	break;
	case 1:
		for (int i=0; i<8; i++) {
			if ((i == 2) | (i == 1)) {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_SET);
			}
			else {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_RESET);
			}
		}
	break;
	case 2:
		for (int i=0; i<8; i++) {
			if ((i == 7) | (i == 2) | (i == 5)) {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_RESET);
			}
			else {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_SET);
			}
		}
	break;
	case 3:
		for (int i=0; i<8; i++) {
			if ((i == 7) | (i == 4) | (i == 5)) {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_RESET);
			}
			else {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_SET);
			}
		}
	break;
	case 4:
		for (int i=0; i<8; i++) {
			if ((i == 7) | (i == 0) | (i == 3) | (i == 4)) {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_RESET);
			}
			else {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_SET);
			}
		}
	break;
	case 5:
		for (int i=0; i<8; i++) {
			if ((i == 7) | (i == 1) | (i == 4)) {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_RESET);
			}
			else {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_SET);
			}
		}
	break;
	case 6:
		for (int i=0; i<8; i++) {
			if ((i == 7) |(i == 1)) {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_RESET);
			}
			else {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_SET);
			}
		}
	break;
	case 7:
		for (int i=0; i<8; i++) {
			if ((i == 7) |(i == 3) | (i == 4) | (i == 6)) {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_RESET);
			}
			else {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_SET);
			}
		}
	break;
	case 8:
		for (int i=0; i<8; i++) {
			if (i == 7) {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_RESET);
			}
			else {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_SET);
			}
		}
	break;
	case 9:
		for (int i=0; i<8; i++) {
			if ((i == 7) |(i == 4)) {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_RESET);
			}
			else {
				GPIO_WritePin(fnd_bcd[i].GPIOx, fnd_bcd[i].pinNum, PIN_SET);
			}
		}
	break;
	}
}
