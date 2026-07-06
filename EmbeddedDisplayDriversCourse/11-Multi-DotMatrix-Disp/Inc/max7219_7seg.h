#ifndef __MAX7219_7SEG_H__
#define __MAX7219_7SEG_H__
#include <stdint.h>

#define  NUM_OF_DISPLAYS		8
#define  NUM_OF_DIGITS		10

#define DISP_1		1
#define DISP_2		2
#define DISP_3		3
#define DISP_4		4
#define DISP_5		5
#define DISP_6		6
#define DISP_7		7
#define DISP_8		8


void max7219_clear(void);
void max7219_init(void);
void max7219_write_number(uint8_t disp_pos, uint8_t num);

#endif
