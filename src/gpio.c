#include "gpio.h"


void ConfigureTestingGPIOs(void)
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