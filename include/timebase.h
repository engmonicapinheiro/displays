#ifndef __TIMEBASE_H
#define __TIMEBASE_H

#include <stdint.h>

#define ONE_SECOND_LOAD     16000000
#define TICK_FREQUENCY      1
#define MAX_DELAY           0xFFFFFFFF

volatile uint32_t g_currentTick;
volatile uint32_t g_currentTick_previous;

void TimebaseInit(void);
void TickIncrement(void);
uint32_t GetTick(void);
void delay(uint32_t delay);


#endif //__TIMEBASE_H