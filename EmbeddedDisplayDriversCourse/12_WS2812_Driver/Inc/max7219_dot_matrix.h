#ifndef __MAX7219_DOT_MATRIX_H__
#define __MAX7219_DOT_MATRIX_H__

#define NUM_OF_DISPLAYS		4

#define set_bit(value,bit)		((value) |= (1u<<(bit)))
#define clear_bit(value,bit)	((value) &= ~(1u<<(bit)))
#define write_bit(value,bit,bitvalue) ( bitvalue ? set_bit(value,bit):clear_bit(value,bit))

#define left 'L'
#define right 'R'

void max7219_dot_mat_init(uint8_t intensity);
void max7219_write_byte(uint8_t byte);
void max7219_set_led(uint8_t row, uint8_t col, uint8_t value);
void max2719_write_char(char c, uint8_t disp_pos);
void max7219_dot_matrix_clear(void);
void max7219_scroll_str(uint8_t *str, uint32_t speed, char direction );

#endif
