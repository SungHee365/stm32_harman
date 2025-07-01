
/* ultrasonic.c */

#include "ultrasonic.h"

volatile uint32_t rising_time = 0;
volatile uint32_t falling_time = 0;
volatile uint8_t  is_rising_edge = 1;
volatile uint8_t  capture_done = 0;

// 거리 측정 시작 (TRIG 10us HIGH)
void UltraSonic_Trigger(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET); // TRIG HIGH
	delay_us(10); // 정확한 10us 지연 (타이머 기반 또는 DWT 방식)
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); // TRIG LOW
}

// 거리 측정 함수 (cm 반환)
int UltraSonic_GetDistance(void)
{
	UltraSonic_Trigger();

	capture_done = 0;
	is_rising_edge = 1;

	uint32_t timeout = HAL_GetTick() + 100;

	// 폴링 대기 (타임아웃 추가 가능)
	while (!capture_done){
		if (HAL_GetTick() > timeout) {
			return -1;  // 실패 시 -1 반환
		}
	}
	uint32_t diff;
	if (falling_time >= rising_time)
		diff = falling_time - rising_time;
	else
		diff = (0xFFFF - rising_time + falling_time);

	// 거리 계산: 시간(us) / 58.0 = cm
	return diff / 58;
}

// 초기화: 입력 캡처 시작
void UltraSonic_Init(void)
{
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
}
