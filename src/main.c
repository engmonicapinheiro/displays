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
    //ButtonInit();
   // SevenSegInit();  //initialise the 7/8 segment display
   // AdcStartConversion();
    //Timer2OutputCompare();
    //Timer3InputCapture();
   // Pc13ExtiInit();

    /*init oled */
    ssd1306Init();

    /* set XY */
    ssd1306GoToXY(0,0);

    /* write string */
    ssd1306PutString("Remote", 1);

    /* set XY */
    ssd1306GoToXY(0,8);

    /* write string */
    ssd1306PutString("Dashboard", 1);

    /* set XY */
    ssd1306GoToXY(0,30);

    /* write string */
    ssd1306PutString("For M2M", 1);


    /* set XY */
    ssd1306GoToXY(0,50);

    /* write string */
    ssd1306PutString("Communication", 1);

    ssd1306UpdateScreen();

    delay(2000);


    printf("Hello from STM32F4.....\n\r");


    while (1)
    {

        // uint32_t adc_sum = 0;
        // for (int i = 0; i < 256; i++)
        // {
        //     adc_sum += AdcRead();
        // }
        // uint32_t adc_avg = adc_sum >> 8;
        // uint8_t value = (uint8_t)((adc_avg * 99UL) / 4095UL);
        // printf("tens=%d ones=%d\n\r", value / 10, value % 10);
        //
        // static uint8_t last_value = 0xFF;
        // if (last_value == 0xFF ||
        //     (value > last_value && value - last_value > 5) ||
        //     (last_value > value && last_value - value > 5))
        // {
        //     last_value = value;
        //     SevenSegSetValue(value / 10, value % 10);
        // }

    }
}

