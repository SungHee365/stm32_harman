/*
 * ap_main.c
 *
 *  Created on: Jun 19, 2025
 *      Author: rhoblack
 */

#include "ap_main.h"
#include <stdio.h>



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2) {
		FND_DispDataCallBack();

		TimeWatch_IncTimeCallBack();
		StopWatch_IncTimeCallBack();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2) {
		Listener_UartCallBack();
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM4 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        if (is_rising_edge)
        {
            rising_time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            is_rising_edge = 0;

            // 다음 캡처를 falling edge로 설정
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
        }
        else
        {
            falling_time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            is_rising_edge = 1;

            // 다음 캡처를 rising edge로 설정
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);

            capture_done = 1;  // 신호 측정 완료 플래그
        }
    }
}

//int dist = 0;


char lcd_buf[16];

int ap_main()
{

	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);

	while(1)
	{
//		dist = UltraSonic_GetDistance();
//		sprintf(lcd_buf, "Dist: %d cm", dist);
//		LCD_writeStringXY(0, 0, lcd_buf);
		Listener_Excute();
		Controller_Excute();
		Presenter_Excute();
//		HAL_Delay(100); // 100ms마다 측정

	}

	return 0;
}

void ap_init()
{
	Listener_Init();
	Presenter_Init();
	UltraSonic_Init();
	DHT11_Init(GPIOA, GPIO_PIN_9);
	Sound_Init();
	Sound_Power();
	Rotate_Init();
	Rotate_On();
	LED_Level_Init();
}



