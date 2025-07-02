/*
 * queue.h
 *
 *  Created on: Jun 25, 2025
 *      Author: rhoblack
 */

#ifndef AP_INC_MYQUEUE_H_
#define AP_INC_MYQUEUE_H_
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUE_SIZE	4

typedef struct {
	int front;
	int rear;
	int typeSize;
	void *queData[QUE_SIZE];
	//void *queData;
}Que_TypeDef;

extern Que_TypeDef qBtnLed;

void MyQue_Init(Que_TypeDef *q, int type_size);
void MyQue_DeInit(Que_TypeDef *q);
int MyisQueFull(Que_TypeDef *q);
int MyisQueEmpty(Que_TypeDef *q);
bool MyenQue(Que_TypeDef *q, void *pData);
bool MydeQue(Que_TypeDef *q, void *pData);
bool MypeekQue(Que_TypeDef *q, void *pData);

#endif /* AP_INC_MYQUEUE_H_ */
