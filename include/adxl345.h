#ifndef __ADXL345_H
#define __ADXL345_H

#include <stdint.h>

/* registers addresses */
#define DEVICE_REG          0x00
#define DEVICE_ADDR         0x53
#define POWER_CTL_REG       0x2D
#define DATA_FORMAT_REG     0x31
#define DATA_START_ADDR     0x32

/* values to write to the registers */
#define SET_MEASURE_B       0x08
#define RESET               0x00
#define FOUR_G              0x01

#define MULTI_BYTE_EN       0x40
#define READ_OPERATION      0x80



void AdxlReadAddress(uint8_t reg);
void AdxlWrite(uint8_t reg, char value);
void AdxlReadValues(uint8_t reg);
void AdxlInit(void);

char data;
const double FOUR_G_SCALE_FACTOR;

#endif //ADXL345_H