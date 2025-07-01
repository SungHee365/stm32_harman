/*
 * Model_DHT11.h
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#ifndef AP_INC_MODEL_DHT11_H_
#define AP_INC_MODEL_DHT11_H_

#include <stdint.h>

typedef struct {
	uint8_t temperature;
	uint8_t humidity;
} dht11_data_t;

void Model_DHT11_Set(uint8_t temp, uint8_t humi);
dht11_data_t Model_DHT11_Get();

#endif /* AP_INC_MODEL_DHT11_H_ */
