#include "OledDisplaySSD1306.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "i2c.h"

const uint16_t font_data [] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // sp
0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x1000, 0x0000, 0x0000,  // !
0x2800, 0x2800, 0x2800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // "
0x2400, 0x2400, 0x7C00, 0x2400, 0x4800, 0x7C00, 0x4800, 0x4800, 0x0000, 0x0000,  // #
0x3800, 0x5400, 0x5000, 0x3800, 0x1400, 0x5400, 0x5400, 0x3800, 0x1000, 0x0000,  // $
0x2000, 0x5400, 0x5800, 0x3000, 0x2800, 0x5400, 0x1400, 0x0800, 0x0000, 0x0000,  // %
0x1000, 0x2800, 0x2800, 0x1000, 0x3400, 0x4800, 0x4800, 0x3400, 0x0000, 0x0000,  // &
0x1000, 0x1000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // '
0x0800, 0x1000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x1000, 0x0800,  // (
0x2000, 0x1000, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x1000, 0x2000,  // )
0x1000, 0x3800, 0x1000, 0x2800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // *
0x0000, 0x0000, 0x1000, 0x1000, 0x7C00, 0x1000, 0x1000, 0x0000, 0x0000, 0x0000,  // +
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x1000, 0x1000,  // ,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000,  // -
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000,  // .
0x0800, 0x0800, 0x1000, 0x1000, 0x1000, 0x1000, 0x2000, 0x2000, 0x0000, 0x0000,  // /
0x3800, 0x4400, 0x4400, 0x5400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // 0
0x1000, 0x3000, 0x5000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // 1
0x3800, 0x4400, 0x4400, 0x0400, 0x0800, 0x1000, 0x2000, 0x7C00, 0x0000, 0x0000,  // 2
0x3800, 0x4400, 0x0400, 0x1800, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // 3
0x0800, 0x1800, 0x2800, 0x2800, 0x4800, 0x7C00, 0x0800, 0x0800, 0x0000, 0x0000,  // 4
0x7C00, 0x4000, 0x4000, 0x7800, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // 5
0x3800, 0x4400, 0x4000, 0x7800, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // 6
0x7C00, 0x0400, 0x0800, 0x1000, 0x1000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000,  // 7
0x3800, 0x4400, 0x4400, 0x3800, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // 8
0x3800, 0x4400, 0x4400, 0x4400, 0x3C00, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // 9
0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000,  // :
0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000, 0x1000, 0x1000, 0x1000,  // ;
0x0000, 0x0000, 0x0C00, 0x3000, 0x4000, 0x3000, 0x0C00, 0x0000, 0x0000, 0x0000,  // <
0x0000, 0x0000, 0x0000, 0x7C00, 0x0000, 0x7C00, 0x0000, 0x0000, 0x0000, 0x0000,  // =
0x0000, 0x0000, 0x6000, 0x1800, 0x0400, 0x1800, 0x6000, 0x0000, 0x0000, 0x0000,  // >
0x3800, 0x4400, 0x0400, 0x0800, 0x1000, 0x1000, 0x0000, 0x1000, 0x0000, 0x0000,  // ?
0x3800, 0x4400, 0x4C00, 0x5400, 0x5C00, 0x4000, 0x4000, 0x3800, 0x0000, 0x0000,  // @
0x1000, 0x2800, 0x2800, 0x2800, 0x2800, 0x7C00, 0x4400, 0x4400, 0x0000, 0x0000,  // A
0x7800, 0x4400, 0x4400, 0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x0000, 0x0000,  // B
0x3800, 0x4400, 0x4000, 0x4000, 0x4000, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000,  // C
0x7000, 0x4800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4800, 0x7000, 0x0000, 0x0000,  // D
0x7C00, 0x4000, 0x4000, 0x7C00, 0x4000, 0x4000, 0x4000, 0x7C00, 0x0000, 0x0000,  // E
0x7C00, 0x4000, 0x4000, 0x7800, 0x4000, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000,  // F
0x3800, 0x4400, 0x4000, 0x4000, 0x5C00, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // G
0x4400, 0x4400, 0x4400, 0x7C00, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // H
0x3800, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x3800, 0x0000, 0x0000,  // I
0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // J
0x4400, 0x4800, 0x5000, 0x6000, 0x5000, 0x4800, 0x4800, 0x4400, 0x0000, 0x0000,  // K
0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x7C00, 0x0000, 0x0000,  // L
0x4400, 0x6C00, 0x6C00, 0x5400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // M
0x4400, 0x6400, 0x6400, 0x5400, 0x5400, 0x4C00, 0x4C00, 0x4400, 0x0000, 0x0000,  // N
0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // O
0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000,  // P
0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x5400, 0x3800, 0x0400, 0x0000,  // Q
0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x4800, 0x4800, 0x4400, 0x0000, 0x0000,  // R
0x3800, 0x4400, 0x4000, 0x3000, 0x0800, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // S
0x7C00, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // T
0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // U
0x4400, 0x4400, 0x4400, 0x2800, 0x2800, 0x2800, 0x1000, 0x1000, 0x0000, 0x0000,  // V
0x4400, 0x4400, 0x5400, 0x5400, 0x5400, 0x6C00, 0x2800, 0x2800, 0x0000, 0x0000,  // W
0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x2800, 0x2800, 0x4400, 0x0000, 0x0000,  // X
0x4400, 0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // Y
0x7C00, 0x0400, 0x0800, 0x1000, 0x1000, 0x2000, 0x4000, 0x7C00, 0x0000, 0x0000,  // Z
0x1800, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1800,  // [
0x2000, 0x2000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0800, 0x0800, 0x0000, 0x0000,  /* \ */
0x3000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x3000,  // ]
0x1000, 0x2800, 0x2800, 0x4400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // ^
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFE00,  // _
0x2000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // `
0x0000, 0x0000, 0x3800, 0x4400, 0x3C00, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000,  // a
0x4000, 0x4000, 0x5800, 0x6400, 0x4400, 0x4400, 0x6400, 0x5800, 0x0000, 0x0000,  // b
0x0000, 0x0000, 0x3800, 0x4400, 0x4000, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000,  // c
0x0400, 0x0400, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000,  // d
0x0000, 0x0000, 0x3800, 0x4400, 0x7C00, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000,  // e
0x0C00, 0x1000, 0x7C00, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // f
0x0000, 0x0000, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0400, 0x7800,  // g
0x4000, 0x4000, 0x5800, 0x6400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // h
0x1000, 0x0000, 0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // i
0x1000, 0x0000, 0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0xE000,  // j
0x4000, 0x4000, 0x4800, 0x5000, 0x6000, 0x5000, 0x4800, 0x4400, 0x0000, 0x0000,  // k
0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // l
0x0000, 0x0000, 0x7800, 0x5400, 0x5400, 0x5400, 0x5400, 0x5400, 0x0000, 0x0000,  // m
0x0000, 0x0000, 0x5800, 0x6400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // n
0x0000, 0x0000, 0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // o
0x0000, 0x0000, 0x5800, 0x6400, 0x4400, 0x4400, 0x6400, 0x5800, 0x4000, 0x4000,  // p
0x0000, 0x0000, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0400, 0x0400,  // q
0x0000, 0x0000, 0x5800, 0x6400, 0x4000, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000,  // r
0x0000, 0x0000, 0x3800, 0x4400, 0x3000, 0x0800, 0x4400, 0x3800, 0x0000, 0x0000,  // s
0x2000, 0x2000, 0x7800, 0x2000, 0x2000, 0x2000, 0x2000, 0x1800, 0x0000, 0x0000,  // t
0x0000, 0x0000, 0x4400, 0x4400, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000,  // u
0x0000, 0x0000, 0x4400, 0x4400, 0x2800, 0x2800, 0x2800, 0x1000, 0x0000, 0x0000,  // v
0x0000, 0x0000, 0x5400, 0x5400, 0x5400, 0x6C00, 0x2800, 0x2800, 0x0000, 0x0000,  // w
0x0000, 0x0000, 0x4400, 0x2800, 0x1000, 0x1000, 0x2800, 0x4400, 0x0000, 0x0000,  // x
0x0000, 0x0000, 0x4400, 0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x1000, 0x6000,  // y
0x0000, 0x0000, 0x7C00, 0x0800, 0x1000, 0x2000, 0x4000, 0x7C00, 0x0000, 0x0000,  // z
0x1800, 0x1000, 0x1000, 0x1000, 0x2000, 0x2000, 0x1000, 0x1000, 0x1000, 0x1800,  // {
0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,  // |
0x3000, 0x1000, 0x1000, 0x1000, 0x0800, 0x0800, 0x1000, 0x1000, 0x1000, 0x3000,  // }
0x0000, 0x0000, 0x0000, 0x7400, 0x4C00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // ~
};

#define FONT_HEIGHT  10
#define FONT_WIDTH   7


/* SSD1306 -> STM32F4 */
/* VCC     -> 3.3V
 * GND     -> GND
 * SCL     -> PB8
 * SDA     -> PB9
 */
static void ssd1306I2cWriteMulti(uint8_t address, uint8_t reg, char *data, uint16_t count);
static char SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

typedef struct
{
    uint16_t currentX;
    uint16_t currentY;
    uint8_t inverted;
    uint8_t initialised;
}SSD1306_t;

static SSD1306_t SSD1306;

uint8_t ssd1306Init(void)
{
    /* initialise I2C module */
    I2CInit();

    /* wait a bit */
    //replace by a delay?
    for (int i = 0; i < 3000; i++){}

    /* run initialisation commands */
    ssd1306RunInitialisationCommands();

    /* clear screen */
    ssd1306Clear();

    /* reset XY position */
    SSD1306.currentX = 0;
    SSD1306.currentY = 0;

    /* set init flag */
    SSD1306.initialised = 1;

    return 1;
}


void ssd1306Clear(void)
{
    /* clear screen */
    ssd1306Fill(SSD1306_COLOR_BLACK);

    /* update screen */
    ssd1306UpdateScreen();

}

void ssd1306Fill(SSD1306_COLOR_t color)
{
    memset(SSD1306_Buffer, (color == SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer));
}

void ssd1306UpdateScreen(void)
{
    for (int m = 0; m < 8; m++)
    {
        SSD1306_WRITE_COMMAND(0xB0 + m);  //send page address command
        SSD1306_WRITE_COMMAND(0x00);
        SSD1306_WRITE_COMMAND(0x10);

        /* write buffer contents to the display */
        ssd1306I2cWriteMulti(SSD1306_I2C_ADDRESS, 0x40, &SSD1306_Buffer[SSD1306_WIDTH * m], SSD1306_WIDTH);
    }
}

void ssd1306DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color)
{
    /* check if the given x and y coordinates are within the display's width and height */
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
    {
        /* if the coordinates are out of bounds, return and do not execute any further code */
        return;
    }

    /* check if the display are inverted */
    if (SSD1306.inverted)
    {
        /* if the pixels are inverted, negate the color value */
        color = (SSD1306_COLOR_t)!color;
    }

    /* set the color of the pixel at a given x and y coordinate */
    if (color == SSD1306_COLOR_WHITE)
    {
        /* if the color is white, OR the buffer value with a bit shift of y mod 8 */
        SSD1306_Buffer[x + (y/8) * SSD1306_WIDTH] |= 1 << (y % 8);
    }
    else
    {
        /* if the color is not white, AND the buffer value with the negation of a bit shift of y mod 8 */
        SSD1306_Buffer[x + (y/8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

void ssd1306GoToXY(uint16_t x, uint16_t y)
{
    SSD1306.currentX = x;
    SSD1306.currentY = y;
}

char ssd1306PutCharacter(char ch, SSD1306_COLOR_t color)
{
    /* Ddeclare variables for looping through the font */
    uint32_t i,b,j;

    /* check if there is enough space on the oled to display the character */
    if (SSD1306_WIDTH <= (SSD1306.currentX + FONT_WIDTH) ||
        SSD1306_HEIGHT <= (SSD1306.currentY + FONT_HEIGHT))
    {
        /* if there is not enough space, return 0 */
        return 0;
    }

    /* go through the font data */
    for (i = 0; i < FONT_HEIGHT; i++)
    {
        /* get the byte of data for the current row of the character */
        b = font_data[(ch - 32) * FONT_HEIGHT + i];

        for (j = 0; j < FONT_WIDTH; j++)
        {
            /* check if the current bit of the byte is set */
            if ((b << j) && 0x8000)
            {
                /* if the bit is set, draw a pixel of the specified color at the current position */
                ssd1306DrawPixel(SSD1306.currentX + j, (SSD1306.currentY + i), (SSD1306_COLOR_t)color);
            }
            else
            {
                /*if the bit is not set, draw a pixel of the opposite color at the current position */
                ssd1306DrawPixel(SSD1306.currentX + j, (SSD1306.currentY + i), (SSD1306_COLOR_t)!color);
            }
        }
    }
    /* increase the current x position for the next character */
    SSD1306.currentX += FONT_WIDTH;

    /* return the character that was written */
    return ch;
}

char ssd1306PutString(char* str, SSD1306_COLOR_t color)
{
    /* write characters in the string one by one to the OLED display */
    while (*str)
    {
        /* write the current character */
        if (ssd1306PutCharacter(*str, color) != *str)
        {
            /* if the function returns an error, return the character that caused the error */
            return *str;
        }

        /* move to the next character in the string */
        str++;
    }

    /* if all characters are written successfully, return 0, i.e. null */
    return *str;
}

void ssd1306DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t color)
{
    int16_t dx, dy, sx, sy, error, e2, i, temp;

    /* check for overflow */
    if (x0 >= SSD1306_WIDTH)
    {
        x0 = SSD1306_WIDTH - 1;
    }

    if (x1 >= SSD1306_WIDTH)
    {
        x1 = SSD1306_WIDTH - 1;
    }

    if (y0 >= SSD1306_HEIGHT)
    {
        y0 = SSD1306_HEIGHT - 1;
    }

    if (y1 >= SSD1306_HEIGHT)
    {
        y1 = SSD1306_HEIGHT - 1;
    }

    /* calculate the change in x and y */
    dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
    dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);

    /* determine the direction of the line */
    sx = (x0 < x1) ? 1 : -1;
    sy = (y0 < y1) ? 1 : -1;

    /* initialise the error term */
    error = ((dx > dy) ? dx : -dy)/2;

    /* check for a vertical line */
    if (dx == 0)
    {
        /* swap y0 and y1 if y1 is smaller than y0 */
        if (y1 < y0)
        {
            temp = y1;
            y1 = y0;
            y0 = temp;
        }

        /* draw a vertical line by looping through the y-coordinate
         * and drawing a pixel at the specified x-coordinate */
        for (i = y0; i <= y1; i++)
        {
            ssd1306DrawPixel(x0, i, color);
        }
        return;
    }

    /* check for horizontal line */
    /* swap x0 and x1 if x1 is smaller than x0 */
    if (dy == 0)
    {
        if (y1 < y0)
        {
            temp = y1;
            y1 = y0;
            y0 = temp;
        }
        if (x1 < x0)
        {
            temp = x1;
            x1 = x0;
            x0 = temp;
        }

        /* draw a horizontal line by looping through the x-coordinates
         * and drawing a pixel at the specified y-coordinate */
        for (i = x0; i <= x1; i++)
        {
            ssd1306DrawPixel(i, y0, color);
        }
        return;
    }

    while (1)
    {
        /* draw the current pixel */
        ssd1306DrawPixel(x0, y0, color);

        /* if the end point has been reached, break out of the loop */
        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        /* calculate the next error value and update the x and y coordinates accordingly */
        e2 = error;
        if (e2 > -dx)
        {
            error -= dy;
            x0 += sx;
        }
        if (e2 < dy)
        {
            error += dx;
            y0 += sy;
        }
    }

}


static void ssd1306I2cWriteMulti(uint8_t address, uint8_t reg, char *data, uint16_t count)
{
    I2cBurstWrite(address, reg, data, count);
}

void ssd1306ScrollLeft(uint8_t startRow, uint8_t endRow)
{
    SSD1306_WRITE_COMMAND(SSD1306_LEFT_HORIZONTAL_SCROLL);
    SSD1306_WRITE_COMMAND(0x00);   //send dummy
    SSD1306_WRITE_COMMAND(startRow);  //start page address
    SSD1306_WRITE_COMMAND(0x00);  //time interval 5 frames
    SSD1306_WRITE_COMMAND(endRow); //end page address
    SSD1306_WRITE_COMMAND(0x00);   //send dummy
    SSD1306_WRITE_COMMAND(0xFF);   //send dummy
    SSD1306_WRITE_COMMAND(SSD1306_ACTIVATE_SCROLL);  //start scroll
}

void ssd1306ScrollRight(uint8_t startRow, uint8_t endRow)
{
    SSD1306_WRITE_COMMAND(SSD1306_RIGHT_HORIZONTAL_SCROLL);
    SSD1306_WRITE_COMMAND(0x00);   //send dummy
    SSD1306_WRITE_COMMAND(startRow);  //start page address
    SSD1306_WRITE_COMMAND(0x00);  //time interval 5 frames
    SSD1306_WRITE_COMMAND(endRow); //end page address
    SSD1306_WRITE_COMMAND(0x00);   //send dummy
    SSD1306_WRITE_COMMAND(0xFF);   //send dummy
    SSD1306_WRITE_COMMAND(SSD1306_ACTIVATE_SCROLL);  //start scroll
}

void ssd1306StopScroll(void)
{
    SSD1306_WRITE_COMMAND(SSD1306_DEACTIVATE_SCROLL);
}

void ssd1306InvertDisplay(uint8_t mode)
{
    if (mode)
    {
        SSD1306_WRITE_COMMAND(SSD1306_INVERT_DISPLAY);
    }
    else
    {
        SSD1306_WRITE_COMMAND(SSD1306_NORMAL_DISPLAY);
    }
}

void ssd1306RunInitialisationCommands(void)
{
    SSD1306_WRITE_COMMAND(0xAE);  //set display off
    SSD1306_WRITE_COMMAND(0x20);  //set memory addressing mode
    SSD1306_WRITE_COMMAND(0x10);  //set page addressing mode
    SSD1306_WRITE_COMMAND(0xB0);  //set page start address for page addressing mode
    SSD1306_WRITE_COMMAND(0xC8);  //set COM output scan direction

    SSD1306_WRITE_COMMAND(0x00); //set low column address
    SSD1306_WRITE_COMMAND(0x10); //set high column address
    SSD1306_WRITE_COMMAND(0x40); //set start line address
    SSD1306_WRITE_COMMAND(0x81); //set contrast control register
    SSD1306_WRITE_COMMAND(0xFF); //set to highest contrast
    SSD1306_WRITE_COMMAND(0xA1); //set segment re-map 0 to 127
    SSD1306_WRITE_COMMAND(0xA6); //set normal display - replace for function
    SSD1306_WRITE_COMMAND(0xA8); //set multiplex ration(1 to 64)
    SSD1306_WRITE_COMMAND(0x3F); //set mux ratio value
    SSD1306_WRITE_COMMAND(0xA4); //set output to follow RAM content: 0xa4
    SSD1306_WRITE_COMMAND(0xD3); //set display offset
    SSD1306_WRITE_COMMAND(0x00); //set display offset value
    SSD1306_WRITE_COMMAND(0xD5); //set display clock divide ratio/oscillator frequency
    SSD1306_WRITE_COMMAND(0xF0); //set divide ratio
    SSD1306_WRITE_COMMAND(0xD9); //set pre-charge period
    SSD1306_WRITE_COMMAND(0x22); //set pre-charge period value
    SSD1306_WRITE_COMMAND(0xDA); //set com pins hardware configuration
    SSD1306_WRITE_COMMAND(0x12); //set com pins value
    SSD1306_WRITE_COMMAND(0xDB); //adjust VCOM regulator
    SSD1306_WRITE_COMMAND(0x20); //set VCOM regulator value
    SSD1306_WRITE_COMMAND(0x8D); //charge pump regulator setting
    SSD1306_WRITE_COMMAND(0x14); //enable charge pump regulator
    SSD1306_WRITE_COMMAND(0xAF); //turn on SSD1306 panel
}



void ssd1306_draw_pixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color)
{
    /* Check if the given x and y coordinates are within the display's width and height */
    if (x >= SSD1306_WIDTH ||y >= SSD1306_HEIGHT) {

        /* If the coordinates are out of bounds, return and do not execute any further code */
        return;
    }

    /* Check if display is inverted */
    if (SSD1306.inverted) {
        /* If the pixels are inverted, negate the color value */
        color = (SSD1306_COLOR_t)!color;
    }

    /* Set the color of the pixel at the given x and y coordinates */
    if (color == SSD1306_COLOR_WHITE) {
        /* If the color is white, OR the buffer value with a bit shift of y mod 8 */
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    }
    else {
        /* If the color is not white, AND the buffer value with the negation of a bit shift of y mod 8 */
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}


void ssd1306_draw_bmp(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color)
{
    uint8_t byte = 0;

    // byteWidth calculates the number of bytes needed to store the image data
    int16_t byteWidth = (w + 7) / 8;

    // iterate through the height of the image
    for(int16_t j = 0; j < h; j++, y++)
    {
        //iterate through the width of the image
        for(int16_t i = 0; i < w; i++)
        {
            // check if the current bit is not the first in the byte
            if(i & 7)
            {
                // shift the byte left by 1
                byte <<= 1;
            }

            else
            {
                // load the next byte of image data
                byte = (*(const unsigned char *)(&bitmap[j * byteWidth + i / 8]));
            }

            // check if the current bit is set
            if(byte & 0x80)
            {

                // draw the pixel at the current x and y position with the specified color
                ssd1306_draw_pixel(x+i, y, color);
            }

        }
    }

}