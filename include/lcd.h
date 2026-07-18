#ifndef LCD_H
#define LCD_H

#include "stm32f407xx.h"
#include <stdint.h>

void LcdGpioInit(void);
void LcdInit(void);
void LcdCommand(uint8_t command);
void LcdData(uint8_t command);
void LcdSetCursorPosition(int row, int line);
void LcdWrite(const char *p);

#define LCD_LINE1   0
#define LCD_LINE2   1


#endif   //LCD_H