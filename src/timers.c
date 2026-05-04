#include "timers.h"
#include "stm32f407xx.h"

void Timer1HzInit(void)
{
    /* enable clock access to TIM2 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* set the prescaler value */
    TIM2->PSC = 1600 - 1;  //16MHZ/1600 = 10.000

    /* set the auto-reload value */
    TIM2->ARR = 10000 - 1;   //10000/1000 = 1Hz

    /* clear the counter */
    TIM2->CNT = 0;

    /* enable the timer */
    TIM2->CR1 |= TIM_CR1_CEN;
}