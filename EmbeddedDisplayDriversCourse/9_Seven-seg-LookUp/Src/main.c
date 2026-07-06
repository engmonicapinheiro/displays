#include <stdio.h>
#include "stm32f4xx.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "seven_seg.h"



int main()
{
	/*Enable FPU*/
	fpu_enable();

	/*Initialize timebase in milliseconds*/
	timebase_msec_init();

	/*Initialize 7/8 segment disp*/
	seven_seg_init();

	while(1)
	{
		for(int i = 0; i <= 9; i++ )
		{
			display_digit(i);
			delay(500);
		}
	}
}

