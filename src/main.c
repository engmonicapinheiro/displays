#include <stdio.h>
#include "stm32f407xx.h"
#include "gpio.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "adc.h"
#include "adxl345.h"


/* Modules to be developed
 * FPU -- ok
 * UART -- ok
 * Timebase --ok
 * GPIO (BSP) --ok
 * ADC --ok
 * SPI
 * I2C --ok
 */

int16_t x, y, z;
float xg, yg, zg;
extern uint8_t dataValues[6];

int main()
{
    TimebaseInit();
    Fpu_enable();
    DebugUartInit();
    AdcInit();
    LedsInit();
    ButtonInit();
    AdxlInit();

    printf("Hello from STM32F4.....\n\r");

    while (1)
    {
       // printf("running.....\r\n");
        //read all 6 values
       AdxlReadValues(DATA_START_ADDR);

        x = ((dataValues[1] << 8) | dataValues[0]);
        y = ((dataValues[3] << 8) | dataValues[2]);
        z = ((dataValues[5] << 8) | dataValues[4]);

        xg = x * FOUR_G_SCALE_FACTOR;
        yg = y * FOUR_G_SCALE_FACTOR;
        zg = z * FOUR_G_SCALE_FACTOR;

       printf("xg = %f\r\n", xg);
       printf("yg = %f\r\n", yg);
       printf("zg = %f\r\n", zg);

    }
}

