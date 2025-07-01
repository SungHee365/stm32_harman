/*
 * dht11.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#include <string.h>
#include <stdio.h>
#include "dht11.h"
#include "tim.h"
#include "Model_DHT11.h"
#include "usart.h"

static GPIO_TypeDef *DHT_PORT;
static uint32_t DHT_PIN;


void delay_us2(uint32_t us) {
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}

void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}



void DHT11_Init(GPIO_TypeDef *port, uint16_t pin)
{
	DHT_PORT = port;
	DHT_PIN = pin;
}

static uint8_t DHT11_ReadBit() {
	while (HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_RESET);
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while (HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_SET);
	uint16_t time = __HAL_TIM_GET_COUNTER(&htim2);
	return (time > 40) ? 1 : 0;
}

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity) {
    uint8_t data[5] = {0};
    char buf[64];

    Set_Pin_Output(DHT_PORT, DHT_PIN);
    HAL_GPIO_WritePin(DHT_PORT, DHT_PIN, GPIO_PIN_RESET);
    HAL_Delay(18);
    HAL_GPIO_WritePin(DHT_PORT, DHT_PIN, GPIO_PIN_SET);
    delay_us2(30);
    Set_Pin_Input(DHT_PORT, DHT_PIN);
    delay_us2(40);

    if (HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_SET) {
        sprintf(buf, "DHT no start signal (1)\r\n");
        HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), 1000);
        return 0;
    }

    delay_us2(80);
    if (HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_RESET) {
        sprintf(buf, "DHT no start signal (2)\r\n");
        HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), 1000);
        return 0;
    }

    delay_us2(80);

    for (int byte = 0; byte < 5; byte++) {
        for (int bit = 0; bit < 8; bit++) {
            data[byte] <<= 1;
            data[byte] |= DHT11_ReadBit();
        }
    }

    sprintf(buf, "DHT raw: %d %d %d %d %d\r\n", data[0], data[1], data[2], data[3], data[4]);
    HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), 1000);

    if (data[4] != (uint8_t)(data[0] + data[1] + data[2] + data[3])) {
        sprintf(buf, "DHT checksum fail\r\n");
        HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), 1000);
        return 0;
    }

    *humidity = data[0];
    *temperature = data[2];
    sprintf(buf, "DHT success temp=%d humi=%d\r\n", *temperature, *humidity);
    HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), 1000);
    return 1;
}

// DHT11 데이터 저장 기능
static dht11_data_t dht11_data = {0};

void Model_DHT11_Set(uint8_t temp, uint8_t humi) {
	dht11_data.temperature = temp;
	dht11_data.humidity = humi;
}

dht11_data_t Model_DHT11_Get() {
	return dht11_data;
}
