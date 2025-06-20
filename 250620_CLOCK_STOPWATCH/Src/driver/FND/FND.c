/*
 * FND.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#include "FND.h"


enum {DIGIT_1, DIGIT_10, DIGIT_100, DIGIT_1000};
typedef struct {
	GPIO_TypeDef *GPIOx;
	uint32_t pinNum;
} FND_TypeDef;



FND_TypeDef fndPin[8] = {
		{GPIOA, 11}, // A
		{GPIOB, 12}, // B
		{GPIOB, 2},  // C
		{GPIOB, 1},	 // D
		{GPIOB, 15}, // E
		{GPIOB, 14}, // F
		{GPIOB, 13}, // G
		{GPIOC, 4}   // Dp
};

FND_TypeDef fndDigitCom[4] = {
		{GPIOA, 12},
		{GPIOC, 5},
		{GPIOC, 6},
		{GPIOC, 8}
};

//static void FND_DispOff(int fndPos);
static void FND_DispOn(int fndPos);
static void FND_DispOffAll();
static void FND_DispDigit(uint16_t digit);

static uint16_t fndDispNum = 0; // fnd main data

void FND_Init()
{
	for(int i=0; i<4; i++){
		GPIO_Init(fndDigitCom[i].GPIOx, fndDigitCom[i].pinNum, OUTPUT);
	}
	for(int i=0; i<8; i++){
		GPIO_Init(fndPin[i].GPIOx, fndPin[i].pinNum, OUTPUT);
	}
}

// write fndDispNum
void FND_WriteData(uint16_t data)
{
	fndDispNum = data;
}

// read fndDispNum
uint16_t FND_ReadData()
{
	return fndDispNum;
}

// display fndDispNum
void FND_DispData(int state,uint32_t c_msecound,uint32_t s_msecound,uint32_t s_dsecound)
{
	static int digitPos = 0;
	// 인터럽트가 발생하면 한 자리 씩 출력 한다.
	digitPos = (digitPos+1) % 4;
	switch(digitPos)
	{
	case DIGIT_1:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum%10);
		FND_DispOn(digitPos);
		break;
	case DIGIT_10:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum/10%10);
		if(state == 2){
			if(s_msecound<5-1) dot_On();
			else dot_Off();
		}
		FND_DispOn(digitPos);
		break;
	case DIGIT_100:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum/100%10);
		if(state == 0){
			if(c_msecound<500-1) dot_On();
			else dot_Off();
		}
		FND_DispOn(digitPos);
		break;
	case DIGIT_1000:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum/1000%10);
		if(state == 2){
			if(s_dsecound<5-1) dot_On();
			else dot_Off();
		}

		FND_DispOn(digitPos);
		break;
	}
}


/*
void FND_DispOff(int fndPos)
{
	// GPIO_Write(GPIOx, Pin, SET);
	GPIO_WritePin(fndDigitCom[fndPos].GPIOx, fndDigitCom[fndPos].pinNum, PIN_SET);
}*/

void FND_DispOn(int fndPos)
{
	// GPIO_Write(GPIOx, Pin, RESET);
	GPIO_WritePin(fndDigitCom[fndPos].GPIOx, fndDigitCom[fndPos].pinNum, PIN_RESET);
}

void FND_DispOffAll()
{
	// GPIO_Write(GPIOx, Pin, SET);
	for (int i=0; i<4; i++){
		GPIO_WritePin(fndDigitCom[i].GPIOx, fndDigitCom[i].pinNum, PIN_SET);
	}
}

void FND_DispDigit(uint16_t digit)
{
	const uint8_t segFont[10] = {
			0x3F,
			0x06,
			0x5B,
			0x4F,
			0x66,
			0x6D,
			0x7D,
			0x07,
			0x7F,
			0x6F
	};
	for (int i=0; i<8; i++) {
			if(!(segFont[digit] & (1<<i))){
				GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].pinNum, PIN_RESET);
			}
			else {
				GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].pinNum, PIN_SET);
			}
		}

}

void dot_On()
{
	GPIO_WritePin(fndPin[7].GPIOx,fndPin[7].pinNum,PIN_RESET);
}

void dot_Off()
{
	GPIO_WritePin(fndPin[7].GPIOx,fndPin[7].pinNum,PIN_SET);
}
