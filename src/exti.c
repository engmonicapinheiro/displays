#include "exti.h"
#include <stdio.h>
#include "stm32f407xx.h"

static void ExtiCallback(void);
volatile uint8_t buttonPressedFlag = 0;


void Pc13ExtiInit(void)
{
    /* disable global interrupts */
    __disable_irq();

    /* enable clock access for GPIOC */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    /* set PC13 as input */
    GPIOC->MODER &= ~(GPIO_MODER_MODER13_0);
    GPIOC->MODER &= ~(GPIO_MODER_MODER13_1);

    /* enable clock access to SYSCFG */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /* select PORTC for EXTI13 */
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

    /* unmask EXTI13 */
    EXTI->IMR |= EXTI_IMR_MR13;

    /* select falling edge trigger */
    EXTI->FTSR |= EXTI_FTSR_TR13;

    /* enable EXTI line in NVIC */
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    /* enable global interrupts */
    __enable_irq();
}

static void ExtiCallback(void)
{
    buttonPressedFlag = 1;
}

void EXTI15_10_IRQHandler(void)
{
    if((EXTI->PR & EXTI_PR_PR13) != 0)
    {
        /* clear the PR flag to rearm it */
        EXTI->PR |= EXTI_PR_PR13;

        /* do something */
        ExtiCallback();
    }
}