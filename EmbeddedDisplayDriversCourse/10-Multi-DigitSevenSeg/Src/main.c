#include <stdio.h>
#include "stm32f4xx.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "bsp.h"
#include "adc.h"
#include "spi.h"
#include "max7219_7seg.h"



#define  GPIOAEN		(1U<<0)
#define  PIN5			(1U<<5)
#define  LED_PIN		PIN5



int main()
{
	/*Enable FPU*/
	fpu_enable();

	/*Initialize timebase*/
	timebase_msec_init();

	/*Initialize debug UART*/
	debug_uart_init();

   /*Init seven seg module*/
	max7219_init();
	delay(100);


	while(1)
	{
		/*test1 :  Write "7" on display number8 */
		//max7219_write_number(DISP_8,7);

		/*test2 :  Count up accross displays*/
		for(int i = 0; i <= NUM_OF_DISPLAYS; i++)
		{
			for(int j = 0; j < NUM_OF_DIGITS; j++)
			{
				max7219_write_number(i,j);
				delay(100);
			}
		}
		delay(100);
		max7219_clear();
	}
}
