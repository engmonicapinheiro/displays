#ifndef __UART_H__
#define __UART_H__

#include "stm32f407xx.h"

#define UART_BAUDRATE (115200)
#define SYS_FREQUENCY (16000000)
#define APB1_CLOCK    (SYS_FREQUENCY)

void DebugUartInit(void);

#endif //UART_H