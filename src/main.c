#include <stdio.h>
#include <stdlib.h>
#include "stm32f407xx.h"
#include "gpio.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "adc.h"
#include "timers.h"
#include "sevenSeg.h"
#include "adxl345.h"


/* Modules to be developed
 * FPU -- ok
 * UART -- ok
 * Timebase --ok
 * GPIO (BSP) --ok
 * ADC --ok
 * timers
 * SPI
 * I2C --ok
 */


int main()
{
    /* initialise timebase in milliseconds */
    TimebaseMsInit();
    Fpu_enable();
    DebugUartInit();
    Timer1HzInit();
    AdcInit();
    LedsInit();
    ButtonInit();

    /* initialise the 7/8 segment display */
    SevenSegInit();

    //AdcStartConversion();
    Timer2OutputCompare();


    printf("Hello from STM32F4.....\n\r");

    while (1)
    {

    }
}

