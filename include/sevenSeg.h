#ifndef __SEVENSEG_H__
#define __SEVENSEG_H__

/* PE15, PB11, PB13, PB15, PD9, PD11, PD13, PD15
 *   a     b     c     d    e    f     g    DP
 */

/* digit 1 -> PE11
 * digit 2 -> PE13
 *
 */

void SevenSegInit(void);
void WriteNumberOne(void);
void WriteNumberTwo(void);
void WriteNumberThree(void);
void WriteNumberFour(void);
void WriteNumberFive(void);
void WriteNumberSix(void);
void WriteNumberSeven(void);
void WriteNumberEight(void);
void WriteNumberNine(void);

#endif //SEVENSEG_H