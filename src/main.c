#include <stdio.h>
#include "stm32f407xx.h"
#include "gpio.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "adc.h"


/* Modules to be developed
 * FPU -- ok
 * UART -- ok
 * Timebase --ok
 * GPIO (BSP) --ok
 * ADC --ok
 * SPI
 * I2C
 */

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
    printf("Hello from STM32F4.....\n\r");

    while (1)
    {
       // printf("running4.....\r\n");
        sensorValue = AdcRead();
        printf("%ld\r\n", sensorValue);
        delay(1);

    }
}

