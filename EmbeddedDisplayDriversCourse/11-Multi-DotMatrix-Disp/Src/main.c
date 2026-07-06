#include <stdio.h>
#include "stm32f4xx.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "bsp.h"
#include "adc.h"
#include "spi.h"
#include "max7219_dot_matrix.h"



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

   /*Init dot matrix module*/
	max7219_dot_mat_init(3);

	/*Print a "A" on display 4*/

	max2719_write_char('A',4);

	/*Print a "heart" on display 2*/
	max2719_write_char(3,2);
	delay(100);


	while(1)
	{
		//max7219_scroll_str((uint8_t *)"EmbeddedExpertIO",180,left);
	}
}
