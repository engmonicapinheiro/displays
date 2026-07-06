#ifndef __CHAR_LCD_H__
#define __CHAR_LCD_H__


#include "stm32f4xx.h"
#include <stdint.h>


#define LCD_LINE1		0
#define LCD_LINE2		1
#define LCD_LINE3		2
#define LCD_LINE4		3

void lcd_gpio_init(void);
void lcd_write(char *p);
void lcd_init(void);
void lcd_set_cursor_pos(int a, int b);

#endif
