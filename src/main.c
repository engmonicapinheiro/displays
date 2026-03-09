#include <stdio.h>
#include "stm32f407xx.h"
#include "gpio.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"


/* Modules to be developed
 * FPU
 * UART
 * Timebase
 * GPIO (BSP)
 * ADC
 */

bool buttonState;

int main()
{
    TimebaseInit();
    Fpu_enable();
    DebugUartInit();
    LedsInit();
    ButtonInit();

    while (1)
    {
        printf("Hello from STM32\n\r");
        //delay(1);
        //TestingBoard();
        
        buttonState = GetButtonState();

        if (buttonState == true)
        {
            GreenLedOn();
        }
        else
        {
            GreenLedOff();
        }
    }
}
