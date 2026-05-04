#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

//setup: connect a jumper wire from PA5 to PA6
int timestamp = 0;

int main()
{
    /* initialise timebase in milliseconds */
    TimebaseMsInit();
    Fpu_enable();
    DebugUartInit();
   // Timer1HzInit();
    AdcInit();
    LedsInit();
   // ButtonInit();
    /* initialise the 7/8 segment display */
   // SevenSegInit();
    //AdcStartConversion();

    Timer2OutputCompare();
    Timer3InputCapture();


    printf("Hello from STM32F4.....\n\r");

    while (1)
    {
       /* wait until edge is captured */
     while(!(TIM3->SR & TIM_SR_CC1IF)){}

      /* read captured value */
     timestamp = TIM3->CCR1;

     printf("%d\n\r", timestamp);

    }
}

