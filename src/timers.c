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

/** Output compare: toggling a pin periodically using the timer */
void Timer2OutputCompare(void)
{
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* set PA5 to alternate function mode */
    GPIOA->MODER &= ~(GPIO_MODER_MODER5_0);
    GPIOA->MODER |= GPIO_MODER_MODER5_1;

    /* set PA5 alternate function type to TIM2_CH1 (AF1) */
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0;

    /* enable clock access to TIM2 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* set the prescaler value */
    TIM2->PSC = 1600 - 1;  //16MHZ/1600 = 10.000

    /* set the auto-reload value */
    TIM2->ARR = 10000 - 1;   //10000/1000 = 1Hz

    /* set the output compare toggle mode */
    TIM2->CCMR1 = (TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1);

    /* enable timer2 channel1 in compare mode */
    TIM2->CCER |= TIM_CCER_CC1E;

    /* clear the counter */
    TIM2->CNT = 0;

    /* enable the timer */
    TIM2->CR1 |= TIM_CR1_CEN;
}