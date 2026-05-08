#include "timers.h"
#include "stm32f407xx.h"
#include "sevenSeg.h"


static void tim2Callback(void);

static volatile uint8_t tens = 0;
static volatile uint8_t ones = 0;

void Timer1HzInit(void)
{
    /* enable clock access to TIM2 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* set the prescaler value */
    TIM2->PSC = 16000 - 1;  //16MHZ/1600 = 10.000

    /* set the auto-reload value */
    TIM2->ARR = 10 - 1;   //10000/1000 = 1Hz

    /* clear the counter */
    TIM2->CNT = 0;

    /* enable the timer */
    TIM2->CR1 |= TIM_CR1_CEN;
}

void Timer1HzInterruptInit(void)
{
    /* enable clock access to TIM2 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* set the prescaler value */
    TIM2->PSC = 160 - 1;  //16MHZ/1600 = 10.000

    /* set the auto-reload value */
    TIM2->ARR = 500 - 1;   //20000/1000 = 2Hz

    /* clear the counter */
    TIM2->CNT = 0;

    /* enable the timer */
    TIM2->CR1 |= TIM_CR1_CEN;

    /* enable TIM interrupt */
    TIM2->DIER |= TIM_DIER_UIE;

    /* enable TIM interrupt in NVIC */
    NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void)
{
    /* clear update interrupt flag */
    TIM2->SR &= ~TIM_SR_UIF;

    /* do something */
    tim2Callback();

}

static void tim2Callback(void)
{
    static uint8_t current_digit = 1;

    /* blank both before switching */
    //GPIOE->BSRR = (GPIO_BSRR_BR_11 | GPIO_BSRR_BR_13);

    if (current_digit == 1)
    {
        SevenSegWrite(1, tens, 0);
        current_digit = 2;
    }
    else
    {
        SevenSegWrite(2, ones, 0);
        current_digit = 1;
    }
}

void SevenSegSetValue(uint8_t t, uint8_t o)
{
    NVIC_DisableIRQ(TIM2_IRQn);
    tens = t;
    ones = o;
    NVIC_EnableIRQ(TIM2_IRQn);
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

//PA6 will capture the frequency from PA5
void Timer3InputCapture(void)
{
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* set PA6 to alternate function mode */
    GPIOA->MODER &= ~(GPIO_MODER_MODER6_0);
    GPIOA->MODER |= GPIO_MODER_MODER6_1;

    /* set PA6 alternate function type to TIM3_CH1 (AF2) */
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL6_1;

    /* enable clock access to TIM3 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    /* set the prescaler value */
    TIM3->PSC = 16000 - 1;  //16MHZ/1600 = 10.000

    /* set CH1 to input capture */
    TIM3->CCMR1 |= TIM_CCMR1_CC1S_0;

    /* set CH1 to capture at rising edge */
    TIM3->CCER |= TIM_CCER_CC1E;      // Enable capture
    TIM3->CCER &= ~TIM_CCER_CC1P;     // Rising edge detection

    /* Enable capture interrupt */
    TIM3->DIER |= TIM_DIER_CC1IE;

    /* enable the timer */
    TIM3->CR1 |= TIM_CR1_CEN;
}