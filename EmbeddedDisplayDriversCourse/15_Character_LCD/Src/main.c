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
#include "char_lcd.h"
#include <stdio.h>

char STR_BUFF[100];
int main()
{
	/*Enable FPU*/
	fpu_enable();


	/*Initialize timebase*/
	timebase_msec_init();

	/*Initialize debug UART*/
	debug_uart_init();

	/*Initialize ADC*/
	pa1_adc_init();

	/*Start conversion*/
	start_conversion();

	/*Initialize char lcd*/
	lcd_gpio_init();
	lcd_init();

	/*Wait 100ms*/
	delay(100);

	lcd_set_cursor_pos(0,LCD_LINE1);
	lcd_write("EmbeddedExpertIO");

	lcd_set_cursor_pos(0,LCD_LINE3);
	lcd_write("Sensor = ");

	lcd_set_cursor_pos(0,LCD_LINE4);
	lcd_write("Time = ");

	while(1)
	{
		sprintf(STR_BUFF,"%d",(int)adc_read());
		lcd_set_cursor_pos(9,LCD_LINE3);
		lcd_write(STR_BUFF);

		sprintf(STR_BUFF,"%d",((int)get_tick()/1000));
		lcd_set_cursor_pos(9,LCD_LINE4);
		lcd_write(STR_BUFF);

		delay(1000);
	}
}
