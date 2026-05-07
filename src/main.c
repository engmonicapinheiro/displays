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
#include "exti.h"
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
    LedsInit();
   // Timer1HzInit();
   // AdcInit();
   // ButtonInit();
    /* initialise the 7/8 segment display */
   // SevenSegInit();
    //AdcStartConversion();
    //Timer2OutputCompare();
    //Timer3InputCapture();

    Pc13ExtiInit();

    printf("Hello from STM32F4.....\n\r");

    while (1)
    {

      if (buttonPressedFlag == 1)
      {
          buttonPressedFlag = 0;
          printf("Button Pressed!\n\r");
      }
    }
}

