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

        SevenSegWrite(1, 1);  // digit 1 (PE11) shows '1'
        delay(500);
        SevenSegWrite(2, 9);  // digit 2 (PE13) shows '9'
        delay(500);
        SevenSegWrite(1, 4);  // digit 1 (PE11) shows '4'
        delay(500);
        SevenSegWrite(2, 0);  // digit 2 (PE13) shows '0'
        delay(500);

    }
}

