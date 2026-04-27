#include "gpio.h"


/* • User LD3: orange LED is a user LED connected to the I/O PD13 of the
STM32F407VGT6.
• User LD4: green LED is a user LED connected to the I/O PD12 of the
STM32F407VGT6.
• User LD5: red LED is a user LED connected to the I/O PD14 of the STM32F407VGT6.
• User LD6: blue LED is a user LED connected to the I/O PD15 of the STM32F407VGT6.

 Push Button: PA0
*/


void LedsInit(void)
{
    //enable clock access to GPIOD
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    //PD12: MODER12
    GPIOD->MODER |= GPIO_MODER_MODE12_0;
    GPIOD->MODER &= ~(GPIO_MODER_MODE12_1);

    //PD13: MODER13
    GPIOD->MODER |= GPIO_MODER_MODE13_0;
    GPIOD->MODER &= ~(GPIO_MODER_MODE13_1);

    //PD14: MODER14
    GPIOD->MODER |= GPIO_MODER_MODE14_0;
    GPIOD->MODER &= ~(GPIO_MODER_MODE14_1);

    //PD15: MODER15
    GPIOD->MODER |= GPIO_MODER_MODE15_0;
    GPIOD->MODER &= ~(GPIO_MODER_MODE15_1);
}


void TestingBoard(void)
{
    GPIOD->ODR ^= (GPIO_ODR_OD12);
    GPIOD->ODR ^= (GPIO_ODR_OD13);
    GPIOD->ODR ^= (GPIO_ODR_OD14);
    GPIOD->ODR ^= (GPIO_ODR_OD15);

    for (int i = 0; i < 1000; ++i);
}

void GreenLedOn(void)
{
    /* set PD12 high */
    GPIOD->ODR |= GPIO_ODR_OD12;

}
void GreenLedOff(void)
{
    /* set PD12 low */
    GPIOD->ODR &= ~(GPIO_ODR_OD12);
}

void ButtonInit(void)
{
    /* enable clock access to PORTA */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    /* set PA0 as an input pin */
    GPIOA->MODER &= ~(GPIO_MODER_MODE0_0);
    GPIOA->MODER &= ~(GPIO_MODER_MODE0_1);
}

bool GetButtonState(void)
{
    /* button is active low */
    /* check if button is pressed */
    if (GPIOA->IDR & GPIO_IDR_ID0)
    {
        return false;
    }
    return true;
}



