#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f407xx.h"
#include<stdbool.h>


void LedsInit(void);
void TestingBoard(void);

void GreenLedOn(void);
void GreenLedOff(void);

//next: pass led number as argument

void ButtonInit(void);
bool GetButtonState(void);

#endif //GPIO_H