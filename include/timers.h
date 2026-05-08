#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <stdint.h>

void Timer1HzInit(void);
void Timer2OutputCompare(void);
void Timer3InputCapture(void);
void Timer1HzInterruptInit(void);
void SevenSegSetValue(uint8_t tens, uint8_t ones);
#endif //TIMERS_H