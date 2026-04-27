#include "sevenSeg.h"
#include "stm32f4xx.h"


void SevenSegInit(void)
{
    /* enable clock access to GPIOB, GPIOD and GPIOE */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

    /* set PE11 and PE13 as output for both digits */
    GPIOE->MODER |= GPIO_MODER_MODE11_0;  //PE11
    GPIOE->MODER &= ~(GPIO_MODER_MODE11_1);

    GPIOE->MODER |= GPIO_MODER_MODE13_0;  //PE13
    GPIOE->MODER &= ~(GPIO_MODER_MODE13_1);

    /* set PE15, PB11, PB13, PB15, PD9, PD11, PD13, PD15 as output pins */
    GPIOE->MODER |= GPIO_MODER_MODE15_0;  //PE15
    GPIOE->MODER &= ~(GPIO_MODER_MODE15_1);

    GPIOB->MODER |= GPIO_MODER_MODE11_0;  //PB11
    GPIOB->MODER &= ~(GPIO_MODER_MODE11_1);

    GPIOB->MODER |= GPIO_MODER_MODE13_0;  //PB13
    GPIOB->MODER &= ~(GPIO_MODER_MODE13_1);

    GPIOB->MODER |= GPIO_MODER_MODE15_0;  //PB15
    GPIOB->MODER &= ~(GPIO_MODER_MODE15_1);

    GPIOD->MODER |= GPIO_MODER_MODE9_0;  //PD9
    GPIOD->MODER &= ~(GPIO_MODER_MODE9_1);

    GPIOD->MODER |= GPIO_MODER_MODE11_0;  //PD11
    GPIOD->MODER &= ~(GPIO_MODER_MODE11_1);

    GPIOD->MODER |= GPIO_MODER_MODE13_0;  //PD13
    GPIOD->MODER &= ~(GPIO_MODER_MODE13_1);

    GPIOD->MODER |= GPIO_MODER_MODE15_0;  //15
    GPIOD->MODER &= ~(GPIO_MODER_MODE15_1);

}

void WriteNumberOne(void)
{
    /* turn on the first digit */
    GPIOE->ODR |= GPIO_ODR_ODR_11;

    /* draw number one */
    GPIOE->ODR &= ~(GPIO_ODR_ODR_15);   //a
    GPIOB->ODR |= GPIO_ODR_ODR_11;      //b
    GPIOB->ODR |= GPIO_ODR_ODR_13;      //c
    GPIOB->ODR &= ~(GPIO_ODR_ODR_15);   //d
    GPIOD->ODR &= ~(GPIO_ODR_ODR_9);    //e
    GPIOD->ODR &= ~(GPIO_ODR_ODR_11);   //f
    GPIOD->ODR &= ~(GPIO_ODR_ODR_13);   //g
}

void WriteNumberTwo(void)
{
    /* turn on the first digit */
    GPIOE->ODR |= GPIO_ODR_ODR_11;

    /* draw number 2 */
    GPIOE->ODR |= GPIO_ODR_ODR_15;   //a
    GPIOB->ODR |= GPIO_ODR_ODR_11;      //b
    GPIOB->ODR &= ~(GPIO_ODR_ODR_13);      //c
    GPIOB->ODR |= GPIO_ODR_ODR_15;   //d
    GPIOD->ODR |= GPIO_ODR_ODR_9;    //e
    GPIOD->ODR &= ~(GPIO_ODR_ODR_11);   //f
    GPIOD->ODR |= GPIO_ODR_ODR_13;   //g
    GPIOD->ODR &= ~(GPIO_ODR_ODR_15);   //DP
}

void WriteNumberThree(void)
{
    /* turn on the first digit */
    GPIOE->ODR |= GPIO_ODR_ODR_11;

    /* draw number 3 */
    GPIOE->ODR |= GPIO_ODR_ODR_15;   //a
    GPIOB->ODR |= GPIO_ODR_ODR_11;      //b
    GPIOB->ODR |= GPIO_ODR_ODR_13;      //c
    GPIOB->ODR |= GPIO_ODR_ODR_15;   //d
    GPIOD->ODR &= ~(GPIO_ODR_ODR_9);    //e
    GPIOD->ODR &= ~(GPIO_ODR_ODR_11);   //f
    GPIOD->ODR |= GPIO_ODR_ODR_13;   //g
    GPIOD->ODR &= ~(GPIO_ODR_ODR_15);   //DP
}

void WriteNumberFour(void)
{
    /* turn on the first digit */
    GPIOE->ODR |= GPIO_ODR_ODR_11;

    /* draw number 4 */
    GPIOE->ODR &= ~(GPIO_ODR_ODR_15);   //a
    GPIOB->ODR |= GPIO_ODR_ODR_11;      //b
    GPIOB->ODR |= GPIO_ODR_ODR_13;      //c
    GPIOB->ODR &= ~(GPIO_ODR_ODR_15);   //d
    GPIOD->ODR &= ~(GPIO_ODR_ODR_9);    //e
    GPIOD->ODR |= GPIO_ODR_ODR_11;   //f
    GPIOD->ODR |= GPIO_ODR_ODR_13;   //g
    GPIOD->ODR &= ~(GPIO_ODR_ODR_15);   //DP
}

void WriteNumberFive(void)
{
    /* turn on the first digit */
    GPIOE->ODR |= GPIO_ODR_ODR_11;

    /* draw number 5 */
    GPIOE->ODR |= (GPIO_ODR_ODR_15);   //a
    GPIOB->ODR &= ~(GPIO_ODR_ODR_11);      //b
    GPIOB->ODR |= GPIO_ODR_ODR_13;      //c
    GPIOB->ODR |= GPIO_ODR_ODR_15;   //d
    GPIOD->ODR &= ~(GPIO_ODR_ODR_9);    //e
    GPIOD->ODR |= GPIO_ODR_ODR_11;   //f
    GPIOD->ODR |= GPIO_ODR_ODR_13;   //g
    GPIOD->ODR &= ~(GPIO_ODR_ODR_15);   //DP
}

void WriteNumberSix(void)
{
    /* turn on the first digit */
    GPIOE->ODR |= GPIO_ODR_ODR_11;

    /* draw number 6 */
    GPIOE->ODR |= (GPIO_ODR_ODR_15);   //a
    GPIOB->ODR &= ~(GPIO_ODR_ODR_11);      //b
    GPIOB->ODR |= GPIO_ODR_ODR_13;      //c
    GPIOB->ODR |= GPIO_ODR_ODR_15;   //d
    GPIOD->ODR |= (GPIO_ODR_ODR_9);    //e
    GPIOD->ODR |= GPIO_ODR_ODR_11;   //f
    GPIOD->ODR |= GPIO_ODR_ODR_13;   //g
    GPIOD->ODR &= ~(GPIO_ODR_ODR_15);   //DP
}

void WriteNumberSeven(void)
{
    /* turn on the first digit */
    GPIOE->ODR |= GPIO_ODR_ODR_11;

    /* draw number 7 */
    GPIOE->ODR |= (GPIO_ODR_ODR_15);   //a
    GPIOB->ODR |= (GPIO_ODR_ODR_11);      //b
    GPIOB->ODR |= GPIO_ODR_ODR_13;      //c
    GPIOB->ODR &= ~(GPIO_ODR_ODR_15);   //d
    GPIOD->ODR &= ~(GPIO_ODR_ODR_9);    //e
    GPIOD->ODR &= ~(GPIO_ODR_ODR_11);   //f
    GPIOD->ODR &= ~(GPIO_ODR_ODR_13);   //g
    GPIOD->ODR &= ~(GPIO_ODR_ODR_15);   //DP
}

void WriteNumberEight(void)
{
    /* turn on the first digit */
    GPIOE->ODR |= GPIO_ODR_ODR_11;

    /* draw number 8 */
    GPIOE->ODR |= (GPIO_ODR_ODR_15);   //a
    GPIOB->ODR |= (GPIO_ODR_ODR_11);      //b
    GPIOB->ODR |= GPIO_ODR_ODR_13;      //c
    GPIOB->ODR |= GPIO_ODR_ODR_15;   //d
    GPIOD->ODR |= (GPIO_ODR_ODR_9);    //e
    GPIOD->ODR |= GPIO_ODR_ODR_11;   //f
    GPIOD->ODR |= GPIO_ODR_ODR_13;   //g
    GPIOD->ODR &= ~(GPIO_ODR_ODR_15);   //DP
}

void WriteNumberNine(void)
{
    /* turn on the first digit */
    GPIOE->ODR |= GPIO_ODR_ODR_11;

    /* draw number 9 */
    GPIOE->ODR |= (GPIO_ODR_ODR_15);   //a
    GPIOB->ODR |= (GPIO_ODR_ODR_11);      //b
    GPIOB->ODR |= GPIO_ODR_ODR_13;      //c
    GPIOB->ODR |= GPIO_ODR_ODR_15;   //d
    GPIOD->ODR &= ~(GPIO_ODR_ODR_9);    //e
    GPIOD->ODR |= GPIO_ODR_ODR_11;   //f
    GPIOD->ODR |= GPIO_ODR_ODR_13;   //g
    GPIOD->ODR &= ~(GPIO_ODR_ODR_15);   //DP
}