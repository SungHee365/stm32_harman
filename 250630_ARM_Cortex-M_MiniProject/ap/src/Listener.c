/*
 * Listener.c
 *
 *  Created on: Jun 24, 2025
 *      Author: rhoblack
 */


#include "Listener.h"
#include "usart.h"

static void Listener_CheckButton();
static void Listener_CheckUart();

static uint8_t rcvData = 0;
static Que_TypeDef uartRxQue;

void Listener_Init()
{
	Button_Init(&hBtnMode, GPIOB, GPIO_PIN_5);
	Button_Init(&hBtnUpPower, GPIOB, GPIO_PIN_3);
	Button_Init(&hBtnDownPower, GPIOA, GPIO_PIN_10);

	Que_Init(&uartRxQue);
	HAL_UART_Receive_IT(&huart2, &rcvData, 1); // uart recv interrupt enable
}

void Listener_Excute()
{
	Listener_CheckButton();
	Listener_CheckUart();
}

void Listener_CheckButton()
{
	static uint32_t prevChkBtnTime = 0;
	uint32_t curTick = HAL_GetTick();
	if (curTick - prevChkBtnTime < 100) {
		return;
	}
	prevChkBtnTime = curTick;

	inputData_TypeDef inputData;

	if (Button_GetState(&hBtnMode) == ACT_RELEASED) {
		inputData.id = MODE;
		inputData.data = MODE_ACT;
		Controller_SetInputData(inputData);
	}
	else if (Button_GetState(&hBtnUpPower) == ACT_PUSHED) {
		inputData.id = UP_POWER;
		inputData.data = UP_ACT;
		Controller_SetInputData(inputData);
	}
	else if (Button_GetState(&hBtnDownPower) == ACT_PUSHED) {
		inputData.id = DOWN_POWER;
		inputData.data = DOWN_ACT;
		Controller_SetInputData(inputData);
	}
}

void Listener_CheckUart()
{
	if (isQueEmpty(&uartRxQue)) {
		return;
	}
	int uartRxData = deQue(&uartRxQue);

	inputData_TypeDef inputData;

	if (uartRxData == 'm') {
		inputData.id = MODE;

		inputData.data = MODE_ACT;
		Controller_SetInputData(inputData);
	}

	else if (uartRxData == 'w') {
		inputData.id = UP_POWER;
		inputData.data = UP_ACT;
		Controller_SetInputData(inputData);
	}
	else if (uartRxData == 's') {
		inputData.id = DOWN_POWER;
		inputData.data = DOWN_ACT;
		Controller_SetInputData(inputData);
	}
	else if (uartRxData == 'd') {
		inputData.id = DISTANCE_MEASURED;
		inputData.data = DISTANCE_ACK;
		Controller_SetInputData(inputData);
	}
	else if (uartRxData == 't') {
		inputData.id = TEMPHUMI;
		inputData.data = TEMP_HUMI_ACK;
		Controller_SetInputData(inputData);
	}

}

void Listener_UartCallBack()
{
	enQue(&uartRxQue, rcvData);
	HAL_UART_Receive_IT(&huart2, &rcvData, 1); // interrupt enable
}



















