#include <stdint.h>
#include "stm32f411xe.h"
#include "GPIO.h"
#include "LedBar.h"

void delay();
void LED_write(uint8_t data);
int main(void)
{
	/*1. Enable clock access to GPIOA */
//	RCC_AHB1EN |= (1U << 0); // RCC_AHB1ENR
	RCC -> AHB1ENR |= (1U <<0);
	RCC -> AHB1ENR |= (1U <<1);
	RCC -> AHB1ENR |= (1U <<2);
	RCC -> AHB1ENR |= (1U <<3);
	/*2. Set PA5 as output pin */
	//GPIOA -> MODER |= (1U << 10); // GPIOA_MODER
	//GPIOA -> MODER &= ~(1U << 11); // GPIOA_MODER
	GPIO_Init(GPIOA, 0, OUTPUT);
	GPIO_Init(GPIOA, 1, OUTPUT);
	GPIO_Init(GPIOA, 4, OUTPUT);
	GPIO_Init(GPIOB, 0, OUTPUT);
	GPIO_Init(GPIOC, 1, OUTPUT);
	GPIO_Init(GPIOC, 0, OUTPUT);
	GPIO_Init(GPIOC, 2, OUTPUT);
	GPIO_Init(GPIOC, 3, OUTPUT);
	uint8_t data = 1;
	uint32_t temp = 0;
	int check = 0;
    while(1)
    {
    	temp = GPIO_ReadPin(GPIOC, 13);
    	if(check == 0){
    		LedBar_Write(data);
    		delay();
    		data = (data <<1) | (data >>7);
    		delay();
    	}
    	else {
    		LedBar_Write(data);
    		delay();
    		data = (data <<7) | (data >>1);
    		delay();
    	}
    	if((temp) & (!GPIO_ReadPin(GPIOC, 13))){
    		check = ~check;
    	}
    }
}


void delay()
{
	for(int i=0; i<100000; i++);
}
