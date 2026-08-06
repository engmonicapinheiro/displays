#ifndef __MAX7219_DOT_MATRIX_DISPLAY_H
#define __MAX7219_DOT_MATRIX_DISPLAY_H

#include <stdint.h>

#define NUM_OF_DISPLAYS  4
#define LEFT 'L'
#define RIGHT 'R'

/* useful macros */
#define SET_BIT(value, bit)             ((value) |= (1U << (bit)))
#define CLEAR_BIT(value, bit)           ((value) &= ~(1U << (bit)))
#define WRITE_BIT(value, bit, bitvalue) (bitvalue ? SET_BIT(value, bit) : CLEAR_BIT(value, bit))

/* functions prototypes */
void DotDisplayInit(uint8_t brightness);
void DotMatrixGpioInit(void);
void DotMatrixWriteByte(uint8_t byte);
void DotDisplaySetRow(uint8_t row, uint8_t value);
void DotDisplayWriteCharacter(char c, uint8_t displayPosition);
void DotDisplayScrollCharacter(char c, uint8_t speed, char direction);
void DotDisplayShiftLeft(void);
void DotDisplayShiftRight(void);
void DotMatrixShiftCharater(char c, uint32_t speed, char direction);
void DotDisplayScrollString(uint8_t *str, uint32_t speed, char direction);
void DotDisplayClear(void);
void DotDisplayWriteCommand(uint8_t address, uint8_t command);
void DotDisplaySetLed(uint8_t row, uint8_t column, uint8_t value);

#endif //MAX7219_DOT_MATRIX_DISPLAY