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
		/*1*/
		GPIOA->ODR &=~(1U<<1);/*a*/
		GPIOA->ODR |=(1U<<9);/*b*/
		GPIOA->ODR |=(1U<<10);/*c*/
		GPIOA->ODR &=~(1U<<4);/*d*/
		GPIOA->ODR &=~(1U<<5);/*e*/
		GPIOA->ODR &=~(1U<<6);/*f*/
		GPIOA->ODR &=~(1U<<7);/*g*/
		GPIOA->ODR &=~(1U<<8);/*dp*/
		delay(500);

		/*2*/
		GPIOA->ODR |=(1U<<1);/*a*/
		GPIOA->ODR |=(1U<<9);/*b*/
		GPIOA->ODR &=~(1U<<10);/*c*/
		GPIOA->ODR |=(1U<<4);/*d*/
		GPIOA->ODR |=(1U<<5);/*e*/
		GPIOA->ODR &=~(1U<<6);/*f*/
		GPIOA->ODR |=(1U<<7);/*g*/
		GPIOA->ODR &=~(1U<<8);/*dp*/
		delay(500);

		/*3*/
		GPIOA->ODR |=(1U<<1);/*a*/
		GPIOA->ODR |=(1U<<9);/*b*/
		GPIOA->ODR |=(1U<<10);/*c*/
		GPIOA->ODR |=(1U<<4);/*d*/
		GPIOA->ODR &=~(1U<<5);/*e*/
		GPIOA->ODR &=~(1U<<6);/*f*/
		GPIOA->ODR |=(1U<<7);/*g*/
		GPIOA->ODR &=~(1U<<8);/*dp*/
		delay(500);

		/*4*/
		GPIOA->ODR &=~(1U<<1);/*a*/
		GPIOA->ODR |=(1U<<9);/*b*/
		GPIOA->ODR |=(1U<<10);/*c*/
		GPIOA->ODR &=~(1U<<4);/*d*/
		GPIOA->ODR &=~(1U<<5);/*e*/
		GPIOA->ODR |=(1U<<6);/*f*/
		GPIOA->ODR |=(1U<<7);/*g*/
		GPIOA->ODR &=~(1U<<8);/*dp*/
		delay(500);

		/*5*/
		GPIOA->ODR |=(1U<<1);/*a*/
		GPIOA->ODR &=~(1U<<9);/*b*/
		GPIOA->ODR |=(1U<<10);/*c*/
		GPIOA->ODR |=(1U<<4);/*d*/
		GPIOA->ODR &=~(1U<<5);/*e*/
		GPIOA->ODR |=(1U<<6);/*f*/
		GPIOA->ODR |=(1U<<7);/*g*/
		GPIOA->ODR &=~(1U<<8);/*dp*/
		delay(500);
		/*6*/
		GPIOA->ODR |=(1U<<1);/*a*/
		GPIOA->ODR &=~(1U<<9);/*b*/
		GPIOA->ODR |=(1U<<10);/*c*/
		GPIOA->ODR |=(1U<<4);/*d*/
		GPIOA->ODR |=(1U<<5);/*e*/
		GPIOA->ODR |=(1U<<6);/*f*/
		GPIOA->ODR |=(1U<<7);/*g*/
		GPIOA->ODR &=~(1U<<8);/*dp*/
		delay(500);
		/*7*/
		GPIOA->ODR |=(1U<<1);/*a*/
		GPIOA->ODR |=(1U<<9);/*b*/
		GPIOA->ODR |=(1U<<10);/*c*/
		GPIOA->ODR &=~(1U<<4);/*d*/
		GPIOA->ODR &=~(1U<<5);/*e*/
		GPIOA->ODR &=~(1U<<6);/*f*/
		GPIOA->ODR &=~(1U<<7);/*g*/
		GPIOA->ODR &=~(1U<<8);/*dp*/
		delay(500);

		/*8*/
		GPIOA->ODR |=(1U<<1);/*a*/
		GPIOA->ODR |=(1U<<9);/*b*/
		GPIOA->ODR |=(1U<<10);/*c*/
		GPIOA->ODR |=(1U<<4);/*d*/
		GPIOA->ODR |=(1U<<5);/*e*/
		GPIOA->ODR |=(1U<<6);/*f*/
		GPIOA->ODR |=(1U<<7);/*g*/
		GPIOA->ODR &=~(1U<<8);/*dp*/
		delay(500);

		/*Write 9*/
		GPIOA->ODR |=(1U<<1);/*a*/
		GPIOA->ODR |=(1U<<9);/*b*/
		GPIOA->ODR |=(1U<<10);/*c*/
		GPIOA->ODR |=(1U<<4);/*d*/
		GPIOA->ODR &=~(1U<<5);/*e*/
		GPIOA->ODR |=(1U<<6);/*f*/
		GPIOA->ODR |=(1U<<7);/*g*/
		GPIOA->ODR &=~(1U<<8);/*dp*/
		delay(500);

		/*Write .*/
		GPIOA->ODR |=(1U<<1);/*a*/
		GPIOA->ODR |=(1U<<9);/*b*/
		GPIOA->ODR |=(1U<<10);/*c*/
		GPIOA->ODR |=(1U<<4);/*d*/
		GPIOA->ODR &=~(1U<<5);/*e*/
		GPIOA->ODR |=(1U<<6);/*f*/
		GPIOA->ODR |=(1U<<7);/*g*/
		GPIOA->ODR |=(1U<<8);/*dp*/
		delay(500);
	}
}

