/*
 * dht11.h
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_DHT11_DHT11_H_
#define DRIVER_DHT11_DHT11_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

void DHT11_Init(GPIO_TypeDef *port, uint16_t pin);
uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity);

void delay_us(uint16_t us);

void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void Model_DHT11_Set(uint8_t temp, uint8_t humi);


#endif /* DRIVER_DHT11_DHT11_H_ */
