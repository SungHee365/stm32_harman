/*
 * ap_main.h
 *
 *  Created on: Jun 19, 2025
 *      Author: rhoblack
 */

#ifndef AP_AP_MAIN_H_
#define AP_AP_MAIN_H_
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "Listener.h"
#include "Controller.h"
#include "Presenter.h"
#include "sound.h"
#include "rotate.h"
#include "UltraSonic.h"
#include "dht11.h"
#include "lcd.h"
#include "Level.h"

int ap_main();
void ap_init();


#endif /* AP_AP_MAIN_H_ */
