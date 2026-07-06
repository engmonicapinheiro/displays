#include "stm32f4xx.h"

/*PA1,PA9,PA10,PA4,PA5,PA6,PA7,PA8*/
/* a,  b,   c,  d,  e,  f,  g,  DP*/

#define GPIOAEN 	(1U<<0)

void seven_seg_init(void)
{
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA1,PA9,PA10,PA4,PA5,PA6,PA7,PA8
	 * as out pins*/

	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER &= ~(1U<<3);

	GPIOA->MODER |= (1U<<18);
	GPIOA->MODER &= ~(1U<<19);

	GPIOA->MODER |= (1U<<20);
	GPIOA->MODER &= ~(1U<<21);

	GPIOA->MODER |= (1U<<8);
	GPIOA->MODER &= ~(1U<<9);

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	GPIOA->MODER |= (1U<<12);
	GPIOA->MODER &= ~(1U<<13);

	GPIOA->MODER |= (1U<<14);
	GPIOA->MODER &= ~(1U<<15);

	GPIOA->MODER |= (1U<<16);
	GPIOA->MODER &= ~(1U<<17);
}
