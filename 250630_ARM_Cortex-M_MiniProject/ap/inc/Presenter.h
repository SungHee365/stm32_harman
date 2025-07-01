/*
 * Presenter.h
 *
 *  Created on: Jun 24, 2025
 *      Author: rhoblack
 */

#ifndef AP_PRESENTER_H_
#define AP_PRESENTER_H_

#include "Model_Watch.h"
#include "Controller.h"
#include "FND.h"
#include "lcd.h"
#include "LedBar.h"
#include "motor.h"
#include "buzzer.h"

void Presenter_Init();
void Presenter_OutData(watch_t watchData);
void Presenter_Excute();
void Presenter_SetMotorPower(uint8_t power);
void Presenter_Led_Check(uint8_t ledData);


#endif /* AP_PRESENTER_H_ */
