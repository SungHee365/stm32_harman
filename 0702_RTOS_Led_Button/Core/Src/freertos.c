/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Button.h"
#include "LedBar.h"
#include "myqueue.h"
#include "lcd.h"
#include <stdio.h>
#include "tim.h"
#include "FND.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
enum {BTN_LED1, BTN_LED2, BTN_LED3};
enum {RUN, STOP, CLEAR};
typedef enum {FND_STATE_RUN, FND_STATE_STOP, FND_STATE_CLEAR} fnd_state_t;
fnd_state_t fndState = FND_STATE_STOP;

typedef struct {
	int id;
}btn_led_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */


//btn_led_t btnData;

osMailQDef(btnMail, 4, btn_led_t);
osMailQId btnMail;

osMailQDef(fndMail, 4, btn_led_t);
osMailQId fndMail;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myButtonTaskHandle;
osThreadId myLedTaskHandle;
osThreadId myFndTaskHandle;
osMessageQId btnLedQueueHandle;
osMutexId LcdMutexHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartButtonTask(void const * argument);
void StartLedTask(void const * argument);
void StartFndTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	/* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */
	/* Create the mutex(es) */
	/* definition and creation of LcdMutex */
	osMutexDef(LcdMutex);
	LcdMutexHandle = osMutexCreate(osMutex(LcdMutex));

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* Create the queue(s) */
	/* definition and creation of btnLedQueue */
	osMessageQDef(btnLedQueue, 16, uint16_t);
	btnLedQueueHandle = osMessageCreate(osMessageQ(btnLedQueue), NULL);

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	btnMail = osMailCreate(osMailQ(btnMail), NULL);
	fndMail = osMailCreate(osMailQ(fndMail), NULL);
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	/* definition and creation of myButtonTask */
	osThreadDef(myButtonTask, StartButtonTask, osPriorityNormal, 0, 128);
	myButtonTaskHandle = osThreadCreate(osThread(myButtonTask), NULL);

	/* definition and creation of myLedTask */
	osThreadDef(myLedTask, StartLedTask, osPriorityNormal, 0, 128);
	myLedTaskHandle = osThreadCreate(osThread(myLedTask), NULL);

	/* definition and creation of myFndTask */
	osThreadDef(myFndTask, StartFndTask, osPriorityIdle, 0, 128);
	myFndTaskHandle = osThreadCreate(osThread(myFndTask), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	HAL_TIM_Base_Start_IT(&htim2);
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartButtonTask */
/**
 * @brief Function implementing the mybuttonTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartButtonTask */
void StartButtonTask(void const * argument)
{
	/* USER CODE BEGIN StartButtonTask */
	Button_Init(&hBtnLed1, GPIOB, GPIO_PIN_5);
	Button_Init(&hBtnLed2, GPIOB, GPIO_PIN_3);
	Button_Init(&hBtnLed3, GPIOA, GPIO_PIN_10);

	LCD_Init(&hi2c1);

	//   MyQue_Init(&qBtnLed, sizeof(btn_led_t));
	btn_led_t *btnData;
	btn_led_t *fndData;

	char str[30];
	uint32_t counter = 0;

	/* Infinite loop */
	for(;;)
	{
		if(Button_GetState(&hBtnLed1) == ACT_RELEASED){
			btnData = osMailAlloc(btnMail, osWaitForever);
			btnData->id = BTN_LED1;

			fndData = osMailAlloc(fndMail, osWaitForever);
			fndData->id = RUN;

			osMailPut(btnMail, btnData);
			osMailPut(fndMail, fndData);
			//         MyenQue(&qBtnLed, &btnData);
			osMutexWait(LcdMutexHandle, osWaitForever);
			LCD_writeStringXY(0, 0, "BTN1");
			osMutexRelease(LcdMutexHandle);
		}
		else if(Button_GetState(&hBtnLed2) == ACT_RELEASED){
			btnData = osMailAlloc(btnMail, osWaitForever);
			btnData->id = BTN_LED2;

			fndData = osMailAlloc(fndMail, osWaitForever);
			fndData->id = STOP;


			osMailPut(btnMail, btnData);
			osMailPut(fndMail, fndData);
			//         MyenQue(&qBtnLed, &btnData);
			osMutexWait(LcdMutexHandle, osWaitForever);
			LCD_writeStringXY(0, 0, "BTN2");
			osMutexRelease(LcdMutexHandle);

		}
		else if(Button_GetState(&hBtnLed3) == ACT_RELEASED){
			btnData = osMailAlloc(btnMail, osWaitForever);
			btnData->id = BTN_LED3;

			fndData = osMailAlloc(fndMail, osWaitForever);
			fndData->id = CLEAR;

			osMailPut(btnMail, btnData);
			osMailPut(fndMail, fndData);
			//         MyenQue(&qBtnLed, &btnData);
			osMutexWait(LcdMutexHandle, osWaitForever);
			LCD_writeStringXY(0, 0, "BTN3");
			osMutexRelease(LcdMutexHandle);

		}
		sprintf(str,":cnt %u", (unsigned int)counter++);
		osMutexWait(LcdMutexHandle, osWaitForever);
		LCD_writeStringXY(0, 4, str);
		osMutexRelease(LcdMutexHandle);
		osDelay(50);
	}
	/* USER CODE END StartButtonTask */
}

/* USER CODE BEGIN Header_StartLedTask */
/**
 * @brief Function implementing the myLedTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartLedTask */
void StartLedTask(void const * argument)
{
	/* USER CODE BEGIN StartLedTask */
	btn_led_t *btnData;
	osEvent evt;
	uint8_t ledData = 0;
	uint32_t prevTime = 0, curTime = 0;
	char str[30];
	uint32_t counter = 0;
	/* Infinite loop */
	for(;;)
	{
		curTime = HAL_GetTick();
		if(curTime - prevTime >= 500){
			prevTime = curTime;
			ledData ^= (1<<0);
			LedBar_Write(ledData);
		}

		evt = osMailGet(btnMail, 0);
		if(evt.status == osEventMail){
			btnData = evt.value.p;
			//         MydeQue(&qBtnLed, &btnData);
			if(btnData->id == BTN_LED1){
				ledData ^= (1<<1);
				LedBar_Write(ledData);
				osMutexWait(LcdMutexHandle, osWaitForever);
				LCD_writeStringXY(1, 0, "LCD1");
				osMutexRelease(LcdMutexHandle);
			}
			else if(btnData->id == BTN_LED2){
				ledData ^= (1<<2);
				LedBar_Write(ledData);
				osMutexWait(LcdMutexHandle, osWaitForever);
				LCD_writeStringXY(1, 0, "LCD2");
				osMutexRelease(LcdMutexHandle);
			}
			else if(btnData->id == BTN_LED3){
				ledData ^= (1<<3);
				LedBar_Write(ledData);
				osMutexWait(LcdMutexHandle, osWaitForever);
				LCD_writeStringXY(1, 0, "LCD3");
				osMutexRelease(LcdMutexHandle);
			}
			osMailFree(btnMail, btnData);

		}
		sprintf(str,":cnt %u", (unsigned int)counter++);
		osMutexWait(LcdMutexHandle, osWaitForever);
		LCD_writeStringXY(1, 4, str);
		osMutexRelease(LcdMutexHandle);
		osDelay(100);
	}
	/* USER CODE END StartLedTask */
}

/* USER CODE BEGIN Header_StartFndTask */
/**
 * @brief Function implementing the myFndTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFndTask */
void StartFndTask(void const * argument)
{
	/* USER CODE BEGIN StartFndTask */
	btn_led_t *fndData;
	osEvent evt;
	uint16_t counter = 0;
	/* Infinite loop */
	for(;;)
		{
			evt = osMailGet(fndMail, 0);
			if(evt.status == osEventMail) {
				fndData = evt.value.p;
				if(fndData->id == RUN) {
					fndState = FND_STATE_RUN;
				}
				else if(fndData->id == STOP) {
					fndState = FND_STATE_STOP;
				}
				else if(fndData->id == CLEAR) {
					fndState = FND_STATE_CLEAR;
				}
				osMailFree(fndMail, fndData);
			}


			if(fndState == FND_STATE_RUN) {
				FND_WriteData(counter++);
			}
			else if(fndState == FND_STATE_STOP) {
				FND_WriteData(counter);
			}
			else if(fndState == FND_STATE_CLEAR) {
				counter = 0;
				FND_WriteData(counter);
				fndState = FND_STATE_STOP;
			}

			osDelay(100);
		}
	/* USER CODE END StartFndTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
