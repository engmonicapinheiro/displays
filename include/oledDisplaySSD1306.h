#ifndef __OLEDDISPLAYSSD1306_H__
#define __OLEDDISPLAYSSD1306_H__

#include "stm32f407xx.h"


#define SSD1306_WIDTH       128
#define SSD1306_HEIGHT      64
#define SSD1306_I2C_ADDRESS 0x3C   //0b0111100

#define SSD1306_WRITE_COMMAND(command)  I2cByteWrite(SSD1306_I2C_ADDRESS, 0x00, command)
#define SSD1306_WRITE_DATA(data)        I2cByteWrite(SSD1306_I2C_ADDRESS, 0x40, data)


typedef enum
{
    SSD1306_COLOR_BLACK = 0x00,    //pixel not set
    SSD1306_COLOR_WHITE = 0x01,    //pixel set
}SSD1306_COLOR_t;


/* commands defined on page 29 of the display datasheet */
#define SSD1306_RIGHT_HORIZONTAL_SCROLL                 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL                  0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL    0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL     0x2A
#define SSD1306_DEACTIVATE_SCROLL                       0x2E
#define SSD1306_ACTIVATE_SCROLL                         0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3
#define SSD1306_NORMAL_DISPLAY                          0xA6
#define SSD1306_INVERT_DISPLAY                          0xA7

void ssd1306ScrollLeft(uint8_t startRow, uint8_t endRow);
void ssd1306ScrollRight(uint8_t startRow, uint8_t endRow);
void ssd1306StopScroll(void);
void ssd1306InvertDisplay(uint8_t mode);
void ssd1306RunInitialisationCommands(void);
uint8_t ssd1306Init(void);
void ssd1306Fill(SSD1306_COLOR_t color);
void ssd1306UpdateScreen(void);
void ssd1306DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);
void ssd1306GoToXY(uint16_t x, uint16_t y);
char ssd1306PutCharacter(char ch, SSD1306_COLOR_t color);
char ssd1306PutString(char* str, SSD1306_COLOR_t color);
void ssd1306DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t color);
void ssd1306Clear(void);
void ssd1306_draw_pixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);
void ssd1306_draw_bmp(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color);


#endif //OLEDDISPLAYSSD1306_H