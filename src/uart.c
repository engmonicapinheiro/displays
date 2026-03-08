#include "uart.h"

/* Two solutions are possible to connect an STM32F407 USART to the VCP on the PC:
• Using an USART to USB dongle from the market connected for instance to
STM32F407 USART2 available on connector P1 pin 14 (PA2: USART2_TX) and P1
pin 13 (PA3: USART2_RX).
*/

void DebugUartInit(void)
{
    /* enable clock access to GPIOA */
    /* set the mode of PA2 to alternate function mode */
    /* set alternate function type to AF07 (UART2_TX) */
    /* enable clock access to UART2 */
    /* configure uart baudrate */
    /* configure transfer direction */
    /* enable the uart module */

}
