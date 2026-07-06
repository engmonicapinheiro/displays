#include "stm32f4xx.h"

/*PA1,PA9,PA10,PA4,PA5,PA6,PA7,PA8*/
/* a,  b,   c,  d,  e,  f,  g,  DP*/

#define GPIOAEN 	(1U<<0)


#define  SEG_A		(1U<<1)
#define  SEG_B		(1U<<9)
#define  SEG_C		(1U<<10)
#define  SEG_D		(1U<<4)
#define  SEG_E		(1U<<5)
#define  SEG_F		(1U<<6)
#define  SEG_G		(1U<<7)
#define  SEG_DP		(1U<<8)


const uint16_t digit_segments[10]={
	  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F), // 0
	  (SEG_B | SEG_C),                                 // 1
	  (SEG_A | SEG_B | SEG_D | SEG_E | SEG_G),         // 2
	  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_G),         // 3
	  (SEG_B | SEG_C | SEG_F | SEG_G),                 // 4
	  (SEG_A | SEG_C | SEG_D | SEG_F | SEG_G),         // 5
	  (SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G), // 6
	  (SEG_A | SEG_B | SEG_C),                         // 7
	  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G), // 8
	  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G)  // 9

};

void display_digit(uint8_t digit)
{
	/*Clear all segments*/
	GPIOA->ODR &=~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G |SEG_DP);

	/*Display digit*/
	GPIOA->ODR |= digit_segments[digit];
}

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
