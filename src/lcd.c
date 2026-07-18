#include "lcd.h"
#include "timebase.h"

static void LcdNibbleWrite(uint8_t data, uint8_t rs);
static void LcdPulseEnable(void);


/* pinout
 *
 * VSS  GND
 * VDD  +5V
 * V0   potentiometer
 * A    +5V (the power supply for LED)
 * K    GND (the power supply for LED)
 *
 * RS   PD1
 * RW   GND
 * E    PD2
 *
 *(using only the last 4 data pins)
 * D4   PD3
 * D5   PD4
 * D6   PD5
 * D7   PD6
 */


void LcdGpioInit(void)
{
    /* enable clock access to GPIOD */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    /* PD1..PD6 as general purpose outputs */
    GPIOD->MODER &= ~(
        GPIO_MODER_MODE1_Msk |
        GPIO_MODER_MODE2_Msk |
        GPIO_MODER_MODE3_Msk |
        GPIO_MODER_MODE4_Msk |
        GPIO_MODER_MODE5_Msk |
        GPIO_MODER_MODE6_Msk
    );

    GPIOD->MODER |=
        GPIO_MODER_MODE1_0 |
        GPIO_MODER_MODE2_0 |
        GPIO_MODER_MODE3_0 |
        GPIO_MODER_MODE4_0 |
        GPIO_MODER_MODE5_0 |
        GPIO_MODER_MODE6_0;

    /* push-pull, no pull-up/pull-down, low speed is fine */
    GPIOD->OTYPER &= ~(
        GPIO_OTYPER_OT1 |
        GPIO_OTYPER_OT2 |
        GPIO_OTYPER_OT3 |
        GPIO_OTYPER_OT4 |
        GPIO_OTYPER_OT5 |
        GPIO_OTYPER_OT6
    );

    GPIOD->PUPDR &= ~(
        GPIO_PUPDR_PUPD1_Msk |
        GPIO_PUPDR_PUPD2_Msk |
        GPIO_PUPDR_PUPD3_Msk |
        GPIO_PUPDR_PUPD4_Msk |
        GPIO_PUPDR_PUPD5_Msk |
        GPIO_PUPDR_PUPD6_Msk
    );

    /* drive everything low initially */
    GPIOD->BSRR =
        GPIO_BSRR_BR1 |
        GPIO_BSRR_BR2 |
        GPIO_BSRR_BR3 |
        GPIO_BSRR_BR4 |
        GPIO_BSRR_BR5 |
        GPIO_BSRR_BR6;
}

static void LcdPulseEnable(void)
{
    GPIOD->BSRR = GPIO_BSRR_BS2;   /* E = 1 */
    delay(1);
    GPIOD->BSRR = GPIO_BSRR_BR2;   /* E = 0 */
    delay(1);
}

static void LcdNibbleWrite(uint8_t data, uint8_t rs)
{
    uint32_t bsrr = 0;

    /* clear RS and data pins first */
    bsrr |= GPIO_BSRR_BR1;
    bsrr |= GPIO_BSRR_BR3;
    bsrr |= GPIO_BSRR_BR4;
    bsrr |= GPIO_BSRR_BR5;
    bsrr |= GPIO_BSRR_BR6;

    /* set RS if sending data */
    if (rs)
    {
        bsrr |= GPIO_BSRR_BS1;
    }

    /* map upper nibble bits [7:4] onto PD6..PD3 */
    if (data & 0x10U) bsrr |= GPIO_BSRR_BS3;   /* D4 -> PD3 */
    if (data & 0x20U) bsrr |= GPIO_BSRR_BS4;   /* D5 -> PD4 */
    if (data & 0x40U) bsrr |= GPIO_BSRR_BS5;   /* D6 -> PD5 */
    if (data & 0x80U) bsrr |= GPIO_BSRR_BS6;   /* D7 -> PD6 */

    GPIOD->BSRR = bsrr;
    LcdPulseEnable();
}

void LcdCommand(uint8_t command)
{
    LcdNibbleWrite(command & 0xF0U, 0U);
    LcdNibbleWrite((uint8_t)(command << 4), 0U);

    if ((command == 0x01U) || (command == 0x02U))
    {
        delay(2);
    }
    else
    {
        delay(1);
    }
}

void LcdData(uint8_t data)
{
    LcdNibbleWrite(data & 0xF0U, 1U);
    LcdNibbleWrite((uint8_t)(data << 4), 1U);
    delay(1);
}

void LcdInit(void)
{
    /* wait for LCD power-up */
    delay(40);

    /*
     * HD44780 4-bit initialisation sequence:
     * send 0x3 three times as high nibble, then 0x2
     */
    LcdNibbleWrite(0x30U, 0U);
    delay(5);

    LcdNibbleWrite(0x30U, 0U);
    delay(1);

    LcdNibbleWrite(0x30U, 0U);
    delay(1);

    LcdNibbleWrite(0x20U, 0U);   /* switch to 4-bit mode */
    delay(1);

    LcdCommand(0x28U);   /* 4-bit, 2 lines, 5x8 font */
    LcdCommand(0x08U);   /* display off */
    LcdCommand(0x01U);   /* clear display */
    LcdCommand(0x06U);   /* entry mode: increment, no shift */
    LcdCommand(0x0CU);   /* display on, cursor off, blink off */
}

void LcdSetCursorPosition(int row, int line)
{
    uint8_t address;

    if (line == LCD_LINE2)
    {
        address = (uint8_t)(0x40 + row);
    }
    else
    {
        address = (uint8_t)row;
    }

    LcdCommand((uint8_t)(0x80U | address));
}

void LcdWrite(const char *p)
{
    while (*p != '\0')
    {
        LcdData((uint8_t)*p);
        p++;
    }
}