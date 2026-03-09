#include <stdio.h>
#include "stm32f407xx.h"
#include "gpio.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"


/* • User LD3: orange LED is a user LED connected to the I/O PD13 of the
STM32F407VGT6.
• User LD4: green LED is a user LED connected to the I/O PD12 of the
STM32F407VGT6.
• User LD5: red LED is a user LED connected to the I/O PD14 of the STM32F407VGT6.
• User LD6: blue LED is a user LED connected to the I/O PD15 of the STM32F407VGT6.
 */

/* Modules to be developed
 * FPU
 * UART
 * GPIO
 * Timebase
 */


int main()
{
    TimebaseInit();
    Fpu_enable();
    DebugUartInit();
    ConfigureTestingGPIOs();

    while (1)
    {
        printf("Hello from STM32\n\r");
        delay(1);
      //  TestingBoard();
    }
}
