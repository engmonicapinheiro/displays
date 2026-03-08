#include "uart.h"
#include <stdint.h>

static uint16_t ComputeUartBaudrate(uint32_t peripheralclock, uint32_t baudrate);
static void UartSetBaudrate(uint32_t peripheralclock, uint32_t baudrate);
static void UartWrite(int ch);

int _write(int fd, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        UartWrite(ptr[i]);
    }
    return len;
}
/* Two solutions are possible to connect an STM32F407 USART to the VCP on the PC:
• Using an USART to USB dongle from the market connected for instance to
STM32F407 USART2 available on connector P1 pin 14 (PA2: USART2_TX) and P1
pin 13 (PA3: USART2_RX).
*/

/* PA3 = orange wire
 * PA2 = yellow wire
 */

void DebugUartInit(void)
{
    /* enable clock access to GPIOA */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* set the mode of PA2 to alternate function mode */
    GPIOA->MODER &= ~(GPIO_MODER_MODE2_0);
    GPIOA->MODER |= GPIO_MODER_MODE2_1;

    /* set alternate function type to AF07 (UART2_TX) */
    // Limpa os 4 bits do AFSEL2 primeiro
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2);

    // Depois define AF7 (0b0111)
    GPIOA->AFR[0] |= (7U << GPIO_AFRL_AFSEL2_Pos);

    /* enable clock access to UART2 */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    /* configure uart baudrate */
    UartSetBaudrate(APB1_CLOCK, UART_BAUDRATE);

    /* configure transfer direction */
    USART2->CR1 = USART_CR1_TE;

    /* enable the uart module */
    USART2->CR1 |= USART_CR1_UE;
}

static uint16_t ComputeUartBaudrate(uint32_t peripheralclock, uint32_t baudrate)
{
    return ((peripheralclock + (baudrate/2U))/baudrate);
}

static void UartSetBaudrate(uint32_t peripheralclock, uint32_t baudrate)
{
    USART2->BRR = ComputeUartBaudrate(peripheralclock, baudrate);
}

static void UartWrite(int ch)
{
    /* make sure transmit data register is empty */
    while(!(USART2->SR & USART_SR_TXE));

    /* write to transmit data register */
    USART2->DR = (ch & 0xFF);
}