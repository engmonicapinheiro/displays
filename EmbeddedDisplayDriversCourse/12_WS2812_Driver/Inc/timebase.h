#ifndef __TIMEBASE_H__
#define __TIMEBASE_H__

#include <stdint.h>
uint32_t get_tick(void);
void delay(uint32_t delay);
void timebase_init(void);
void timebase_msec_init(void);
void sys_clck_config_80mhz(void);

#define MAX_DELAY	0xFFFFFFFF
#endif
