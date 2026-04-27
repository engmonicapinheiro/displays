#include <stdio.h>
#include "stm32f407xx.h"
#include "gpio.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "adc.h"
#include "adxl345.h"
#include "sevenSeg.h"

/* Modules to be developed
 * FPU -- ok
 * UART -- ok
 * Timebase --ok
 * GPIO (BSP) --ok
 * ADC --ok
 * SPI
 * I2C --ok
 */


int main()
{
    /* initialise timebase in milliseconds */
    TimebaseMsInit();
    Fpu_enable();
    DebugUartInit();
    AdcInit();
    LedsInit();
    ButtonInit();

    /* initialise the 7/8 segment display */
    SevenSegInit();

    printf("Hello from STM32F4.....\n\r");

    while (1)
    {
        WriteNumberOne();
        delay(500);
        WriteNumberTwo();
        delay(500);
        WriteNumberThree();
        delay(500);
        WriteNumberFour();
        delay(500);
        WriteNumberFive();
        delay(500);
        WriteNumberSix();
        delay(500);
        WriteNumberSeven();
        delay(500);
        WriteNumberEight();
        delay(500);
        WriteNumberNine();
        delay(500);
    }
}

