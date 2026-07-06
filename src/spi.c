#include "spi.h"

#define CS_PORT  GPIOA
#define CS_PIN   GPIO_ODR_OD4

void SpiInit(uint32_t baud)
{
    /* enable clock access to GPIOA and SPI1 */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    /* PA5 (SCK), PA6 (MISO), PA7 (MOSI) -> alternate function mode */
    GPIOA->MODER &= ~(GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0);
    GPIOA->MODER |=  (GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1);

    /* alternate function AF5 (SPI1) */
    GPIOA->AFR[0] |= (5U << GPIO_AFRL_AFSEL5_Pos);
    GPIOA->AFR[0] |= (5U << GPIO_AFRL_AFSEL6_Pos);
    GPIOA->AFR[0] |= (5U << GPIO_AFRL_AFSEL7_Pos);

    /* PA4 as CS (output, push-pull) */
    GPIOA->MODER |= GPIO_MODER_MODE4_0;
    GPIOA->MODER &= ~(GPIO_MODER_MODE4_1);
    CS_PORT->BSRR = CS_PIN;  /* CS high (inactive) */

    /* configure SPI1 */
    SPI1->CR1 = SPI_CR1_MSTR | baud | SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR2 = 0;

    /* enable SPI1 */
    SPI1->CR1 |= SPI_CR1_SPE;
}

void SpiCsLow(void)
{
    CS_PORT->BSRR = CS_PIN << 16;
}

void SpiCsHigh(void)
{
    CS_PORT->BSRR = CS_PIN;
}

uint8_t SpiTransfer(uint8_t data)
{
    while (!(SPI1->SR & SPI_SR_TXE)) {}
    SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_RXNE)) {}
    return (uint8_t)SPI1->DR;
}

void SpiBurstWrite(uint8_t *data, int len)
{
    for (int i = 0; i < len; i++)
    {
        while (!(SPI1->SR & SPI_SR_TXE)) {}
        SPI1->DR = data[i];
    }
    while (SPI1->SR & SPI_SR_BSY) {}
}

void SpiBurstRead(uint8_t *data, int len)
{
    for (int i = 0; i < len; i++)
    {
        while (!(SPI1->SR & SPI_SR_TXE)) {}
        SPI1->DR = 0xFF;
        while (!(SPI1->SR & SPI_SR_RXNE)) {}
        data[i] = (uint8_t)SPI1->DR;
    }
}
