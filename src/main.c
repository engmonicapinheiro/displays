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
#include "oledDisplaySSD1306.h"
#include "adxl345.h"
#include "lcd.h"
#include "max7219DotMatrixDisplay.h"

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
    Fpu_enable();
    DebugUartInit();
    //initialise timebase
    TimebaseMsInit();
  //  LedsInit();
   // Timer1HzInterruptInit();
   // AdcInit();
   // AdcStartConversion();
    //Timer2OutputCompare();
    //Timer3InputCapture();
   // Pc13ExtiInit();

   /* initialise the dot matrix display */
    DotDisplayInit(5);
    delay(100);

    DotDisplayWriteCharacter('M', 4);
    //printf("Hello from STM32F4.....\n\r");


    while (1)
    {


    }
}

