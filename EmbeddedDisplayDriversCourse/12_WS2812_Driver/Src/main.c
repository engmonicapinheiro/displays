#include <stdio.h>
#include "stm32f4xx.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "bsp.h"
#include "adc.h"
#include "spi.h"
#include "ws2812.h"
#include "math.h"
#include "stdlib.h"






int main()
{
	/*Enable FPU*/
	fpu_enable();


	/*Sys clock config*/
	sys_clck_config_80mhz();

	/*Initialize timebase*/
	timebase_msec_init();

	/*Initialize debug UART*/
	debug_uart_init();

	 /*Init led strip*/
	ws2812_init();


	while(1)
	{
		/*Turn leds on from first to last*/
		 for(int i = 0; i <  NUM_OF_LEDS; i++)
		 {
			 srand(get_tick());
			 ws2812_set_led(i,random()%256,random()%256,random()%256);
			 ws2812_set_brightness(50);
			 ws2812_display();
			 delay(random()%100);
		 }
		 delay(200);

		 /*Turn leds off from last to first*/
		 for(int i = NUM_OF_LEDS; i >=0  ; i--)
		 {
			 ws2812_set_led(i,0,0,0);
			 ws2812_set_brightness(40);
			 ws2812_display();
			 delay(random()%100);
		 }
		 delay(200);

	}
}
