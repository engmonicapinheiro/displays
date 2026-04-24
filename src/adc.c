#include "adc.h"
#include "stm32f407xx.h"

void AdcInit(void)
{
    /*** configure the ADC GPIO pin ***/

    /* enable clock access to GPIOA */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* set PA1 mode to analog mode */
    GPIOA->MODER |= GPIO_MODER_MODER1_0;
    GPIOA->MODER |= GPIO_MODER_MODER1_1;

    /*** configure the ADC module ***/
    /* enable clock access to the ADC module */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* set the conversion sequence start */
    ADC1->SQR3 = ADC_SQR3_SQ1_0;

    /* set the conversion sequence length */
    ADC1->SQR1 = 0x00;

    /* enable the ADC module */
    ADC1->CR2 |= ADC_CR2_ADON;
}

void AdcStartConversion(void)
{
    /* enable continuous conversion */
    ADC1->CR2 |= ADC_CR2_CONT;

    /*start the ADC conversion */
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

//polling
uint32_t AdcRead(void)
{
    /* wait for conversion to be complete */
    while (!(ADC1->SR & ADC_SR_EOC));

    /* read converted value */
    return (ADC1->DR);
}
