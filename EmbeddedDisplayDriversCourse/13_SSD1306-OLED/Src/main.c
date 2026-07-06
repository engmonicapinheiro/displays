#include <stdio.h>
#include "stm32f4xx.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "bsp.h"
#include "adc.h"
#include "spi.h"
#include "ssd1306.h"
#include "math.h"
#include "stdlib.h"
#include "horse_anim.h"




static void run_horse_animation(void);


int main()
{
	/*Enable FPU*/
	fpu_enable();


	/*Initialize timebase*/
	timebase_msec_init();

	/*Initialize debug UART*/
	debug_uart_init();

	 /*Init oled*/
	ssd1306_init();

	 /*Set XY*/
	ssd1306_goto_xy(0,0);
	/*Write string*/
	ssd1306_put_str("Remote",  1);

	 /*Set XY*/
	ssd1306_goto_xy(0,8);
	/*Write string*/
	ssd1306_put_str("Dashboard",  1);

	 /*Set XY*/
	ssd1306_goto_xy(0,30);
	/*Write string*/
	ssd1306_put_str("For M2M",  1);

	 /*Set XY*/
	ssd1306_goto_xy(0,50);
	/*Write string*/
	ssd1306_put_str("Communication",  1);

	/*Update screen*/
	ssd1306_update_screen();
	delay(2000);

	/*Scroll the entire screen*/
	ssd1306_scroll_right(0,7);
	delay(2000);

	/*Scroll the entire screen*/
	ssd1306_scroll_left(0,7);
	delay(2000);

	/*Scroll the screen*/
	ssd1306_scroll_right(0,2);
	delay(2000);

	/*Scroll the screen*/
	ssd1306_scroll_left(0,2);
	delay(2000);
	/*stop scroll*/
	ssd1306_stop_scroll();

	/*Invert display*/
	ssd1306_invert_display(1);
	delay(2000);

	/*Set display to normal mode*/
	ssd1306_invert_display(0);
	delay(2000);

	/*Clear Display*/
	ssd1306_clear();

	while(1)
	{

		/*Run horse animation*/
		run_horse_animation();

	}
}


static void run_horse_animation(void)
{
	/*Clear display*/
	ssd1306_clear();

	/*draw first horse*/
	ssd1306_draw_bmp(0,0,horse1,128,64,1);

	/*Update display*/
	ssd1306_update_screen();

	ssd1306_clear();
	ssd1306_draw_bmp(0,0,horse2,128,64,1);
	ssd1306_update_screen();

	ssd1306_clear();
	ssd1306_draw_bmp(0,0,horse3,128,64,1);
	ssd1306_update_screen();

	ssd1306_clear();
	ssd1306_draw_bmp(0,0,horse4,128,64,1);
	ssd1306_update_screen();

	ssd1306_clear();
	ssd1306_draw_bmp(0,0,horse5,128,64,1);
	ssd1306_update_screen();

	ssd1306_clear();
	ssd1306_draw_bmp(0,0,horse6,128,64,1);
	ssd1306_update_screen();


	ssd1306_clear();
	ssd1306_draw_bmp(0,0,horse7,128,64,1);
	ssd1306_update_screen();

	ssd1306_clear();
	ssd1306_draw_bmp(0,0,horse8,128,64,1);
	ssd1306_update_screen();


	ssd1306_clear();
	ssd1306_draw_bmp(0,0,horse9,128,64,1);
	ssd1306_update_screen();


	ssd1306_clear();
	ssd1306_draw_bmp(0,0,horse10,128,64,1);
	ssd1306_update_screen();
}
