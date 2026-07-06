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
#include "ST7735.h"

#define YMAX	5000
#define YMIN	0


static void draw_sensor_grph_axs(void);
static void draw_sys_info_bar(void);
static void plot_sensor_data(void);


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

	/*Initialize ST7735*/
	st7735_init();

	/*Draw axes*/
	draw_sensor_grph_axs();

	/*Draw information bar*/
	draw_sys_info_bar();


	while(1)
	{
		draw_sys_info_bar();
		plot_sensor_data();
	}
}

static void draw_sensor_grph_axs(void)
{
	st7735_drw_axs(AXISCOLOR,BGCOLOR,"Time","ADC",LIGHTCOLOR,"",0,YMAX,YMIN);
}

static void draw_sys_info_bar(void)
{
	st7735_drw_str(1,0,"CPU =",ST7735_COLOR_GREEN);
	st7735_drw_str(7,0,"75%",ST7735_COLOR_BLUE);

	st7735_drw_str(11,0,"Temp =",ST7735_COLOR_GREEN);
	st7735_drw_str(18,0,"30",ST7735_COLOR_BLUE);

}

static void plot_sensor_data(void)
{
	st7735_plt_pt(adc_read(),ST7735_COLOR_GREEN);
	st7735_plt_incr();
}
