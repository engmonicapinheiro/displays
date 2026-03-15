#include <stdio.h>
#include "stm32f407xx.h"
#include "gpio.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "adc.h"


/* Modules to be developed
 * FPU
 * UART
 * Timebase
 * GPIO (BSP)
 * ADC
 */

bool buttonState;
uint32_t sensorValue;

int main()
{
    TimebaseInit();
    Fpu_enable();
    DebugUartInit();
    AdcInit();
    LedsInit();
    ButtonInit();

    AdcStartConversion();

    while (1)
    {
       // printf("Hello from STM32\n\r");
        //delay(1);
        //TestingBoard();
        sensorValue = AdcRead();

    }
}
