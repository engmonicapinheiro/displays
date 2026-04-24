#ifndef __I2C_H
#define __I2C_H

#include "stm32f407xx.h"

/* PB8 ... SCL
 * PB9 ... SDA
 */

#define I2C_100KHZ   80  //0b 0101 0000
#define SD_MODE_MAX_RISE_TIME  17

void I2CInit(void);
void I2cByteRead(char slaveAddress, char memAddress, char *data);
void I2cBurstRead(char slaveAddress, char memAddress, char *, int nrBytes);
void I2cByteWrite(char slaveAddress, char memAddress, char *data);
void I2cBurstWrite(char slaveAddress, char memAddress, char *data, int nrBytes);


#endif //I2C_H