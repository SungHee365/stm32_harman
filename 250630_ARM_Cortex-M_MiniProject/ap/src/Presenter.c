/*
 * Presenter.c
 *
 *  Created on: Jun 24, 2025
 *      Author: rhoblack
 */
#include "Presenter.h"
#include <string.h>
#include <stdio.h>
#include "usart.h"

//static void Presenter_DispTimeWatch(watch_t watchData);
//static void Presenter_DispStopWatch(watch_t watchData);
static void Presenter_DispDistance(watch_t watchData);
static void Presenter_DispTempHumi(watch_t watchData);

//static void Presenter_DispFndTimeWatch(watch_t watchData);
//static void Presenter_DispFndStopWatch(watch_t watchData);
static void Presenter_DispFndDistance(watch_t watchData);
static void Presenter_DispFndTempHumi(watch_t watchData);

//static void Presenter_DispMonitorTimeWatch(watch_t watchData);
//static void Presenter_DispMonitorStopWatch(watch_t watchData);
static void Presenter_DispMonitorDistance(watch_t watchData);
static void Presenter_DispMonitorTempHumi(watch_t watchData);

//static void Presenter_DispLCDTimeWatch(watch_t watchData);
//static void Presenter_DispLCDStopWatch(watch_t watchData);
static void Presenter_DispLCDDistance(watch_t watchData);
static void Presenter_DispLCDTempHumi(watch_t watchData);

static void Presenter_Dist_motor(watch_t watchData);
static void Presenter_Temp_Humi_motor(watch_t watchData);




static watch_t dispData = {DISTANCE, 0, 0, 0, 0, 0,0};

void Presenter_Init()
{
	LCD_Init(&hi2c1);
}

void Presenter_OutData(watch_t watchData)
{
	memcpy(&dispData, &watchData, sizeof(watch_t));
}

void Presenter_Excute()
{
	/*
	if (dispData.id == TIME_WATCH){
		Presenter_DispTimeWatch(dispData);
	}
	else if(dispData.id == STOP_WATCH) { // STOP_WATCH
		Presenter_DispStopWatch(dispData);
	}
	*/
	if(dispData.id == DISTANCE) {
		Presenter_DispDistance(dispData);
	}
	else {
		Presenter_DispTempHumi(dispData);
	}
}

/*
void Presenter_DispTimeWatch(watch_t watchData)
{
	Presenter_DispFndTimeWatch(watchData);
	Presenter_DispMonitorTimeWatch(watchData);
	Presenter_DispLCDTimeWatch(watchData);
}

void Presenter_DispStopWatch(watch_t watchData)
{
	Presenter_DispFndStopWatch(watchData);
	Presenter_DispMonitorStopWatch(watchData);
	Presenter_DispLCDStopWatch(watchData);
}
*/
void Presenter_DispDistance(watch_t watchData)
{
	Presenter_DispFndDistance(watchData);
	Presenter_DispMonitorDistance(watchData);
	Presenter_DispLCDDistance(watchData);
	Presenter_Dist_motor(watchData);
}

void Presenter_DispTempHumi(watch_t watchData)
{
	Presenter_DispFndTempHumi(watchData);
	Presenter_DispMonitorTempHumi(watchData);
	Presenter_DispLCDTempHumi(watchData);
	Presenter_Temp_Humi_motor(watchData);
}
/*
void Presenter_DispFndTimeWatch(watch_t watchData)
{
	FND_WriteData(watchData.hour*100 + watchData.min);

	FND_WriteDp(FND_DP_1000|FND_DP_10|FND_DP_1, FND_DP_OFF);

	if (watchData.msec < 500) {
		FND_WriteDp(FND_DP_100, FND_DP_ON);
	}
	else {
		FND_WriteDp(FND_DP_100, FND_DP_OFF);
	}
}

void Presenter_DispFndStopWatch(watch_t watchData)
{
	FND_WriteData((watchData.min % 10 * 1000) + (watchData.sec * 10) + (watchData.msec/100));

	FND_WriteDp(FND_DP_100|FND_DP_1, FND_DP_OFF);

	if (watchData.msec%100 < 50) {
		FND_WriteDp(FND_DP_10, FND_DP_ON);
	}
	else {
		FND_WriteDp(FND_DP_10, FND_DP_OFF);
	}

	if (watchData.msec < 500) {
		FND_WriteDp(FND_DP_1000, FND_DP_ON);
	}
	else {
		FND_WriteDp(FND_DP_1000, FND_DP_OFF);
	}
}
*/
void Presenter_DispFndDistance(watch_t watchData)
{
	if (watchData.dist < 0) return;
	FND_WriteData(watchData.dist);
	FND_WriteDp(FND_DP_1000 | FND_DP_100 | FND_DP_10 | FND_DP_1, FND_DP_OFF);
}

void Presenter_DispFndTempHumi(watch_t watchData)
{
	if (watchData.temp < 0) return;
	if (watchData.humi < 0) return;
	FND_WriteData(watchData.temp * 100 + watchData.humi);
	FND_WriteDp(FND_DP_1000 | FND_DP_100 | FND_DP_10 | FND_DP_1, FND_DP_OFF);
}
/*
void Presenter_DispMonitorTimeWatch(watch_t watchData)
{
	char str[50];
	sprintf(str,"Time Watch : %02d:%02d:%02d.%03d\n", watchData.hour, watchData.min, watchData.sec, watchData.msec);
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000);
}

void Presenter_DispMonitorStopWatch(watch_t watchData)
{
	char str[50];
	sprintf(str,"Stop Watch : %02d:%02d:%02d.%03d\n", watchData.hour, watchData.min, watchData.sec, watchData.msec);
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000);
}
*/
void Presenter_DispMonitorDistance(watch_t watchData)
{
	if (watchData.dist < 0) return;

	char str[50];
	sprintf(str,"Distance : %03dcm\n", watchData.dist);
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000);
}

void Presenter_DispMonitorTempHumi(watch_t watchData)
{
	if (watchData.temp < 0) return;
	if (watchData.humi < 0) return;
	char str[50];
	sprintf(str,"Temp_Humi : %02dC %02d%%\n", watchData.temp, watchData.humi);
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000);
}
/*
void Presenter_DispLCDTimeWatch(watch_t watchData)
{
	char str[50];
	sprintf(str,"TW:%02d:%02d:%02d.%03d       ", watchData.hour, watchData.min, watchData.sec, watchData.msec);
	LCD_writeStringXY(0, 0, str);
}

void Presenter_DispLCDStopWatch(watch_t watchData)
{
	char str[50];
	sprintf(str,"SW: %02d:%02d:%02d.%03d       ", watchData.hour, watchData.min, watchData.sec, watchData.msec);
	LCD_writeStringXY(0, 0, str);
}
*/
void Presenter_DispLCDDistance(watch_t watchData)
{
	if (watchData.dist < 0) return;
	char lcd_buf[50];
	char clear[50];
	sprintf(lcd_buf, "Dist: %3d cm       ", watchData.dist);
	sprintf(clear, "                ");
	LCD_writeStringXY(0, 0, lcd_buf);
	LCD_writeStringXY(1, 0, clear);
}

void Presenter_DispLCDTempHumi(watch_t watchData)
{
	if (watchData.temp < 0) return;
	if (watchData.humi < 0) return;
	char temp[50];
	char humi[50];
	sprintf(temp, "temp: %2dC        ", watchData.temp);
	sprintf(humi, "humi: %2d%%        ", watchData.humi);
	LCD_writeStringXY(0, 0, temp);
	LCD_writeStringXY(1, 0, humi);
}

void Presenter_Dist_motor(watch_t watchData)
{
//	static uint8_t motorOn = 0;

	if (watchData.dist > 0 && watchData.dist <= 30) {
//	    if (!motorOn) {
	        Motor_Start();
//	        motorOn = 1;
//	    }
	} else {
//	    if (motorOn) {
	        Motor_Stop();
//	        motorOn = 0;
//	    }
	}
}

void Presenter_Temp_Humi_motor(watch_t watchData){
//    static uint8_t motorOn = 0;  // 모터 상태 유지

    // 기준 이상이면 모터 작동
    if ((watchData.temp > 27) || (watchData.humi > 70)) {
            Motor_Start();
    }
    // 기준 이하로 떨어지면 모터 정지
    else {
            Motor_Stop();
    }
}

void Presenter_SetMotorPower(uint8_t power)
{
	Motor_SetDuty(power);
}

void Presenter_Led_Check(uint8_t ledData)
{
	LedBar_Write(ledData);
}
