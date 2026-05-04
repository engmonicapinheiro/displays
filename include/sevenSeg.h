#ifndef __SEVENSEG_H__
#define __SEVENSEG_H__

#include <stdint.h>


/* PE15, PB11, PB13, PB15, PD9, PD11, PD13, PD15
 *   a     b     c     d    e    f     g    DP
 */

/* digit 1 -> PE11
 * digit 2 -> PE13
 *
 */


#define SEGMENT_A  (1U << 0)   //PE15
#define SEGMENT_B  (1U << 1)   //PB11
#define SEGMENT_C  (1U << 2)   //PB13
#define SEGMENT_D  (1U << 3)   //PB15
#define SEGMENT_E  (1U << 4)   //PD9
#define SEGMENT_F  (1U << 5)   //PD11
#define SEGMENT_G  (1U << 6)   //PD13
#define SEGMENT_DP (1U << 7)   //PD15


void SevenSegInit(void);
void WriteNumberOne(void);
void WriteNumberTwo(void);
void WriteNumberThree(void);
void WriteNumberFour(void);
void WriteNumberFive(void);
void WriteNumberSix(void);
void WriteNumberSeven(void);
void WriteNumberEight(void);void WriteNumberNine(void);

void SevenSegWrite(uint8_t digit, uint8_t value, uint8_t dp);


#endif //SEVENSEG_H