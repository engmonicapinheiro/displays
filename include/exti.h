#ifndef __EXTI_H__
#define __EXTI_H__

#include <stdint.h>

void Pc13ExtiInit(void);

extern volatile uint8_t buttonPressedFlag;

#endif  //EXTI_H